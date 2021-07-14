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

rt_list_t rt_thread_priority_table[RT_THREAD_PRIORITY_MAX];
extern struct rt_thread idle;
extern struct rt_thread rt_flag1_thread;
extern struct rt_thread rt_flag2_thread;

static rt_int16_t rt_scheduler_lock_nest;

void rt_system_scheduler_init(void)
{
    register rt_base_t offset;

    for (offset = 0; offset < RT_THREAD_PRIORITY_MAX; offset++)
    {
        rt_list_init(&rt_thread_priority_table[offset]);
    }

    rt_current_thread = RT_NULL;
}

void rt_system_scheduler_start(void)
{
    register struct rt_thread *to_thread;

    to_thread = rt_list_entry(rt_thread_priority_table[0].next,
                              struct rt_thread,
                              tlist);
    rt_current_thread = to_thread;

    rt_hw_context_switch_to((rt_uint32_t)&to_thread->sp);
}

void rt_schedule(void)
{
    struct rt_thread *to_thread;
    struct rt_thread *from_thread;

#if 0
    if (rt_current_thread == rt_list_entry(rt_thread_priority_table[0].next,
                                           struct rt_thread,
                                           tlist))
    {
        from_thread = rt_current_thread;
        to_thread = rt_list_entry(rt_thread_priority_table[1].next,
                                  struct rt_thread,
                                  tlist);
        rt_current_thread = to_thread;
    }
    else
    {
        from_thread = rt_current_thread;
        to_thread = rt_list_entry(rt_thread_priority_table[0].next,
                                  struct rt_thread,
                                  tlist);
        rt_current_thread = to_thread;
    }
#else
    if (rt_current_thread == &idle)
    {
        if (rt_flag1_thread.remaining_tick == 0)
        {
            from_thread = rt_current_thread;
            to_thread = &rt_flag1_thread;
            rt_current_thread = to_thread;
        }
        else if (rt_flag2_thread.remaining_tick == 0)
        {
            from_thread = rt_current_thread;
            to_thread = &rt_flag2_thread;
            rt_current_thread = to_thread;
        }
        else
        {
            return;
        }
    }
    else
    {
        if (rt_current_thread == &rt_flag1_thread)
        {
            if (rt_flag2_thread.remaining_tick == 0)
            {
                from_thread = rt_current_thread;
                to_thread = &rt_flag2_thread;
                rt_current_thread = to_thread;
            }
            else if (rt_current_thread->remaining_tick != 0)
            {
                from_thread = rt_current_thread;
                to_thread = &idle;
                rt_current_thread = to_thread;
            }
            else
            {
                return;
            }
        }
        else if (rt_current_thread == &rt_flag2_thread)
        {
            if (rt_flag1_thread.remaining_tick == 0)
            {
                from_thread = rt_current_thread;
                to_thread = &rt_flag1_thread;
                rt_current_thread = to_thread;
            }
            else if (rt_current_thread->remaining_tick != 0)
            {
                from_thread = rt_current_thread;
                to_thread = &idle;
                rt_current_thread = to_thread;
            }
            else
            {
                return;
            }
        }
    }
#endif

    rt_hw_context_switch((rt_uint32_t)&from_thread->sp, (rt_uint32_t)&to_thread->sp);
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
