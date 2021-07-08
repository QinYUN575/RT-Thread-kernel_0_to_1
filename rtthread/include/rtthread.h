/**
 * @file rtthread.h
 * @author TsMax (QinYUN575@Foxmail.com)
 * @brief
 * @version 0.1
 * @date 2021-07-02
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef __RT_THREAD_H__
#define __RT_THREAD_H__

#include <rtdef.h>
#include <rtconfig.h>
#include <rtservice.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Thread interface
 */
rt_err_t rt_thread_init(struct rt_thread *thread,
                    void (*entry)(void *parameter),
                    void *parameter,
                    void *stack_start,
                    rt_uint32_t stack_size);

/**
 * Schedule service
 */
void rt_system_scheduler_init(void);
void rt_system_scheduler_start(void);

void rt_schedule(void);

#ifdef __cplusplus
}
#endif

#endif
