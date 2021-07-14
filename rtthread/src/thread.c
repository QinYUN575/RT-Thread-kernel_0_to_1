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
                        rt_uint32_t stack_size)
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

    return RT_EOK;
}


void rt_thread_delay(rt_tick_t tick)
{
    struct rt_thread *thread;

    thread = rt_current_thread;
    thread->remaining_tick = tick;

    rt_schedule();
}
