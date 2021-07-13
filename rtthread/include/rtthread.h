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

#include <rthw.h>
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
                    const char *name,
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

void rt_enter_critical(void);
void rt_exit_critical(void);
rt_int16_t rt_critical_level(void);

/**
 * Kernel object interface
 */
struct rt_object_information *
rt_object_get_information(enum rt_object_class_type type);

void rt_object_init(struct rt_object            *object,
                    enum rt_object_class_type   type,
                    const char                  *name);


char *rt_strncpy(char *dst, const char *str, rt_ubase_t n);

#ifdef __cplusplus
}
#endif

#endif
