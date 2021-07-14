/**
 * @file idle.c
 * @author TsMax (QinYUN575@Foxmail.com)
 * @brief
 * @version 0.1
 * @date 2021-07-13
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <rthw.h>
#include <rtthread.h>

extern rt_list_t rt_thread_priority_table[RT_THREAD_PRIORITY_MAX];

#define IDLE_THREAD_STACK_SIZE 512
// ALIGN(RT_ALIGN_SIZE)
static rt_uint8_t rt_thread_stack[IDLE_THREAD_STACK_SIZE];

struct rt_thread idle;

rt_ubase_t rt_idletask_ctr = 0;

void rt_thread_idle_entry(void *paramter)
{
    while (1)
    {
        rt_idletask_ctr++;
    }
}

/**
 * @ingroup SystemInit
 *
 * @brief This function will initialize idle thread, then start it.
 *
 * @note This function must be invoked when system init.
 */
void rt_thread_idle_init(void)
{
    /* initialize thread */
    rt_thread_init(&idle,
                   "idle",
                   rt_thread_idle_entry,
                   RT_NULL,
                   &rt_thread_stack[0],
                   sizeof(rt_thread_stack));

    rt_list_insert_before(&(rt_thread_priority_table[RT_THREAD_PRIORITY_MAX-1]), &(idle.tlist));
}
