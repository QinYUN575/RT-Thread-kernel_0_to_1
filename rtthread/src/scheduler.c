/**
 * @file scheduler.c
 * @author TsMax (QinYUN575@Foxmail.com)
 * @brief
 * @version 0.1
 * @date 2021-07-06
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <rthw.h>
#include <rtthread.h>

struct rt_thread *rt_current_thread;
rt_uint32_t rt_thread_ready_priority_group;
rt_uint8_t rt_current_priority;

rt_list_t rt_thread_priority_table[RT_THREAD_PRIORITY_MAX];
extern struct rt_thread idle;

static rt_uint16_t rt_scheduler_lock_nest;

void rt_system_scheduler_init(void)
{
    register rt_base_t offset;
    for (offset = 0; offset < RT_THREAD_PRIORITY_MAX; offset++)
    {
        rt_list_init(&rt_thread_priority_table[offset]);
    }

    rt_current_priority = RT_THREAD_PRIORITY_MAX - 1;
    rt_current_thread = RT_NULL;
    rt_thread_ready_priority_group = 0;
}

void rt_system_scheduler_start(void)
{
#if 0
    register struct rt_thread *to_thread;

    to_thread = rt_list_entry(rt_thread_priority_table[0].next,
                              struct rt_thread,
                              tlist);
    rt_current_thread = to_thread;

    rt_hw_context_switch_to((rt_uint32_t)&to_thread->sp);
#else
    register struct rt_thread *to_thread;
    register rt_ubase_t highest_ready_priority;

    highest_ready_priority = __rt_ffs(rt_thread_ready_priority_group) - 1;
    to_thread = rt_list_entry(rt_thread_priority_table[highest_ready_priority].next,
                              struct rt_thread,
                              tlist);

    rt_current_thread = to_thread;
    rt_hw_context_switch_to((rt_uint32_t)&to_thread->sp);
#endif
}

void rt_schedule_insert_thread(struct rt_thread *thread)
{
    register rt_base_t level;

    level = rt_hw_interrupt_disable();

    thread->stat = RT_THREAD_READY;

    rt_list_insert_before(&(rt_thread_priority_table[thread->current_priority]), &(thread->tlist));

    rt_thread_ready_priority_group |= (thread->number_mask);

    rt_hw_interrupt_enable(level);
}

void rt_schedule_remove_thread(struct rt_thread *thread)
{
    register rt_base_t level;
    level = rt_hw_interrupt_disable();

    rt_list_remove(&(thread->tlist));

    if (rt_list_isempty(&(rt_thread_priority_table[thread->current_priority])))
    {
        rt_thread_ready_priority_group &= ~(thread->number_mask);
    }
    rt_hw_interrupt_enable(level);
}

void rt_schedule(void)
{
    register rt_base_t level;
    struct rt_thread *from_thread;
    struct rt_thread *to_thread;
    rt_uint32_t highest_ready_priority;

    level = rt_hw_interrupt_disable();

    if (rt_scheduler_lock_nest == 0)
    {
        highest_ready_priority = __rt_ffs(rt_thread_ready_priority_group) - 1;
        to_thread = rt_list_entry(rt_thread_priority_table[highest_ready_priority].next,
                                  struct rt_thread,
                                  tlist);

        if (to_thread != rt_current_thread)
        {
            rt_current_priority = (rt_uint8_t)highest_ready_priority;
            from_thread = rt_current_thread;
            rt_current_thread = to_thread;

            rt_hw_context_switch((rt_uint32_t)&from_thread->sp, (rt_uint32_t)&to_thread->sp);
        }
    }
    rt_hw_interrupt_enable(level);
}

/**
 * @brief The function will lock the thread scheduler.
 */
void rt_enter_critical(void)
{
    register rt_base_t level;

    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    /**
     * the maximal number of nest is RT_INT16_MAX, which is big enough and does
     * not check here.
     */
    rt_scheduler_lock_nest++;

    /* enable interrupt */
    rt_hw_interrupt_enable(level);
}

/**
 * @brief The function will unlock the thread scheduler.
 */
void rt_exit_critical(void)
{
    register rt_base_t level;

    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    rt_scheduler_lock_nest--;
    if (rt_scheduler_lock_nest <= 0)
    {
        rt_scheduler_lock_nest = 0;
        /* enable interrupt */
        rt_hw_interrupt_enable(level);

        if (rt_current_thread)
        {
            /* if scheduler is started, do a scheduler. */
            rt_schedule();
        }
    }

    /* enable interrupt */
    rt_hw_interrupt_enable(level);
}

/**
 * @brief Get the scheduler lock level
 *
 * @return the level of the scheduler lock. 0 means unlocked.
 */
rt_int16_t rt_critical_level(void)
{
    return rt_scheduler_lock_nest;
}
