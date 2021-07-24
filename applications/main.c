/**
 * @file main.c
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
#include "ARMCM3.h"

rt_uint8_t flag1;
rt_uint8_t flag2;
rt_uint8_t flag3;

struct rt_thread rt_flag1_thread;
struct rt_thread rt_flag2_thread;
struct rt_thread rt_flag3_thread;

ALIGN(RT_ALIGN_SIZE)
/* 定义线程栈 */
rt_uint8_t rt_flag1_thread_stack[512];
rt_uint8_t rt_flag2_thread_stack[512];
rt_uint8_t rt_flag3_thread_stack[512];

/* 线程声明 */
void flag1_thread_entry(void *arg);
void flag2_thread_entry(void *arg);
void flag3_thread_entry(void *arg);

void delay(uint32_t count);

int main(void)
{
    rt_hw_interrupt_disable();
    SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);

    rt_system_scheduler_init();

    rt_thread_idle_init();

    rt_thread_init(&rt_flag1_thread,
                   "thread1",
                   flag1_thread_entry,
                   RT_NULL,                         /* 线程形参 */
                   &rt_flag1_thread_stack[0],       /* 线程栈起始地址 */
                   sizeof(rt_flag1_thread_stack),   /* 线程栈大小，单位为字节 */
                   2);

    // rt_list_insert_before(&(rt_thread_priority_table[0]), &(rt_flag1_thread.tlist));
    rt_thread_startup(&rt_flag1_thread);

    rt_thread_init(&rt_flag2_thread,
                   "thread2",
                   flag2_thread_entry,
                   RT_NULL,                         /* 线程形参 */
                   &rt_flag2_thread_stack[0],       /* 线程栈起始地址 */
                   sizeof(rt_flag2_thread_stack),   /* 线程栈大小，单位为字节 */
                   3);
    
    // rt_list_insert_before(&(rt_thread_priority_table[1]), &(rt_flag2_thread.tlist));
    rt_thread_startup(&rt_flag2_thread);

    rt_thread_init(&rt_flag3_thread,
                   "thread3",
                   flag3_thread_entry,
                   RT_NULL,                         /* 线程形参 */
                   &rt_flag3_thread_stack[0],       /* 线程栈起始地址 */
                   sizeof(rt_flag3_thread_stack),   /* 线程栈大小，单位为字节 */
                   4);

    rt_thread_startup(&rt_flag3_thread);
    
    rt_system_scheduler_start();
}

void flag1_thread_entry(void *arg)
{
    for (;;)
    {
        flag1 = 1;
        rt_thread_delay(4);
        flag1 = 0;
        rt_thread_delay(4);
    }
}

void flag3_thread_entry(void *arg)
{
    for (;;)
    {
        flag3 = 1;
        rt_thread_delay(1);
        flag3 = 0;
        rt_thread_delay(1);
    }
}

void flag2_thread_entry(void *arg)
{
//    rt_base_t level2;
    for (;;)
    {
        flag2 = 1;
        //level2 = rt_hw_interrupt_disable();
        rt_enter_critical();
        rt_thread_delay(3);
        rt_exit_critical();
        //rt_hw_interrupt_enable(level2);
        flag2 = 0;
        rt_thread_delay(3);
    }
}


void SysTick_Handler(void)
{
    rt_interrupt_enter();

    rt_tick_increase();

    rt_interrupt_leave();
}
