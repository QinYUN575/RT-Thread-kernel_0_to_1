/**
 * @file clock.c
 * @author TsMax (QinYUN575@Foxmail.com)
 * @brief
 * @version 0.1
 * @date 2021-07-14
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <rtthread.h>
#include <rthw.h>

static rt_tick_t rt_tick = 0;
extern rt_list_t rt_thread_priority_table[RT_THREAD_PRIORITY_MAX];
extern rt_uint32_t rt_thread_ready_priority_group;


void rt_tick_increase(void)
{
    struct rt_thread *thread;
    ++rt_tick;

    thread = rt_thread_self();
    --thread->remaining_tick;
    if (thread->remaining_tick == 0)
    {
        thread->remaining_tick = thread->init_tick;
        rt_thread_yield();
    }

    rt_timer_check();
}

rt_tick_t rt_tick_get(void)
{
    return rt_tick;
}