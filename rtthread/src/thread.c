/**
 * @file rtthread.c
 * @author TsMax (QinYUN575@Foxmail.com)
 * @brief
 * @version 0.1
 * @date 2021-07-02
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <rthw.h>
#include <rtthread.h>

extern struct rt_thread *rt_current_thread;
extern rt_uint32_t rt_thread_ready_priority_group;

/**
 * @brief
 *
 * @param thread
 * @param entry
 * @param parameter
 * @param stack_start
 * @param stack_size
 * @return rt_err_t
 */
rt_err_t rt_thread_init(struct rt_thread *thread,
                        const char *name,
                        void (*entry)(void *parameter),
                        void *parameter,
                        void *stack_start,
                        rt_uint32_t stack_size,
                        rt_uint8_t priority)
{
    /* initialize thread object */
    rt_object_init((rt_object_t)thread, RT_Object_Class_Thread, name);
    rt_list_init(&(thread->tlist));

    thread->entry = (void *)entry;
    thread->parameter = parameter;

    thread->stack_addr = stack_start;
    thread->stack_size = stack_size;

    thread->sp = (void *)rt_hw_stack_init(thread->entry,
                                          thread->parameter,
                                          (void *)((char *)thread->stack_addr + thread->stack_size - 4));
    
    thread->init_priority = priority;
    thread->current_priority = priority;
    thread->number_mask = 0;
    thread->error = RT_EOK;
    thread->stat = RT_THREAD_INIT;

    return RT_EOK;
}

void rt_thread_delay(rt_tick_t tick)
{
#if 0
    struct rt_thread *thread;

    thread = rt_current_thread;
    thread->remaining_tick = tick;

    rt_schedule();

#else
    register rt_base_t level;
    struct rt_thread *thread;

    level = rt_hw_interrupt_disable();

    thread = rt_current_thread;
    thread->remaining_tick = tick;

    thread->stat = RT_THREAD_SUSPEND;
    rt_thread_ready_priority_group &= ~thread->number_mask;

    rt_hw_interrupt_enable(level);
    rt_schedule();
#endif
}

rt_err_t rt_thread_resume(rt_thread_t thread)
{
    register rt_base_t level;

    if ((thread->stat & RT_THREAD_STAT_MASK) != RT_THREAD_SUSPEND)
    {
        return -RT_ERROR;
    }

    level = rt_hw_interrupt_disable();
    rt_list_remove(&(thread->tlist));
    rt_hw_interrupt_enable(level);

    rt_schedule_insert_thread(thread);

    return RT_EOK;
}

rt_thread_t rt_thread_self(void)
{
    return rt_current_thread;
}

rt_err_t rt_thread_startup(rt_thread_t thread)
{
    thread->current_priority = thread->init_priority;
    thread->number_mask = 1L << thread->current_priority;

    thread->stat = RT_THREAD_SUSPEND;

    rt_thread_resume(thread);

    if (rt_thread_self() != RT_NULL)
    {
        rt_schedule();
    }

    return RT_EOK;
}