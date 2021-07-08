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

    rt_hw_context_switch((rt_uint32_t)&from_thread->sp, (rt_uint32_t)&to_thread->sp);
}