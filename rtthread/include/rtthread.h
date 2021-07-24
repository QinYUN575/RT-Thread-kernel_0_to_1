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
                    rt_uint32_t stack_size,
                    rt_uint8_t priority,
                    rt_uint32_t tick);

void rt_thread_delay(rt_tick_t tick);
void rt_tick_increase(void);
void rt_thread_idle_init(void);
rt_thread_t rt_thread_self(void);

rt_err_t rt_thread_startup(struct rt_thread *thread);
rt_err_t rt_thread_resume(rt_thread_t thread);
void rt_thread_timeout(void *parameter);
rt_err_t rt_thread_sleep(rt_tick_t tick);
rt_err_t rt_thread_suspend(struct rt_thread *thread);
rt_err_t rt_thread_yield(void);

/**
 * Schedule service
 */
void rt_system_scheduler_init(void);
void rt_system_scheduler_start(void);
void rt_schedule(void);
void rt_schedule_insert_thread(struct rt_thread *thread);
void rt_schedule_remove_thread(struct rt_thread *thread);

void rt_enter_critical(void);
void rt_exit_critical(void);
rt_int16_t rt_critical_level(void);


void rt_interrupt_enter(void);
void rt_interrupt_leave(void);

rt_tick_t rt_tick_get(void);


void rt_system_timer_init(void);
void rt_timer_check(void);
rt_err_t rt_timer_start(rt_timer_t timer);
rt_err_t rt_timer_stop(rt_timer_t timer);
rt_err_t rt_timer_control(rt_timer_t timer, int cmd, void *arg);
void rt_timer_init(rt_timer_t timer,
                   const char *name,
                   void (*timeout_func)(void *parameter),
                   void *parameter,
                   rt_tick_t time,
                   rt_uint8_t flag);

int __rt_ffs(int value);

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
