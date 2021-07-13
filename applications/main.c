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

#include <rtdef.h>
#include <rtthread.h>
#include <rtservice.h>
#include "ARMCM3.h"

rt_uint8_t flag1;
rt_uint8_t flag2;

extern rt_list_t rt_thread_priority_table[RT_THREAD_PRIORITY_MAX];

struct rt_thread rt_flag1_thread;
struct rt_thread rt_flag2_thread;

ALIGN(RT_ALIGN_SIZE)
/* 定义线程栈 */
rt_uint8_t rt_flag1_thread_stack[512];
rt_uint8_t rt_flag2_thread_stack[512];

/* 线程声明 */
void flag1_thread_entry(void *arg);
void flag2_thread_entry(void *arg);

void delay(uint32_t count);

int main(void)
{
    rt_system_scheduler_init();

    rt_thread_init(&rt_flag1_thread,
                   "thread1",
                   flag1_thread_entry,
                   RT_NULL,                        /* 线程形参 */
                   &rt_flag1_thread_stack[0],      /* 线程栈起始地址 */
                   sizeof(rt_flag1_thread_stack)); /* 线程栈大小，单位为字节 */

    rt_list_insert_before(&(rt_thread_priority_table[0]), &(rt_flag1_thread.tlist));

    rt_thread_init(&rt_flag2_thread,
                   "thread2",
                   flag2_thread_entry,
                   RT_NULL,                        /* 线程形参 */
                   &rt_flag2_thread_stack[0],      /* 线程栈起始地址 */
                   sizeof(rt_flag2_thread_stack)); /* 线程栈大小，单位为字节 */
    rt_list_insert_before(&(rt_thread_priority_table[1]), &(rt_flag2_thread.tlist));

    rt_system_scheduler_start();
}

void delay(uint32_t count)
{
    for (; count != 0; count--)
        ;
}

void flag1_thread_entry(void *arg)
{
    for (;;)
    {
        flag1 = 1;
        delay(100);
        flag1 = 0;
        delay(100);

        rt_schedule();
    }
}

void flag2_thread_entry(void *arg)
{
    rt_base_t level2;
    for (;;)
    {
        level2 = rt_hw_interrupt_disable();
//        flag1 = 3;
        flag2 = 1;
        delay(100);
//        flag1 = 4;
        flag2 = 0;
        delay(100);
        rt_hw_interrupt_enable(level2);
        rt_schedule();
    }
}
