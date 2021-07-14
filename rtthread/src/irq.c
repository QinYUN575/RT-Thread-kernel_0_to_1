/**
 * @file irq.c
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


/**
 * @addtogroup Kernel
 */

volatile rt_uint8_t rt_interrupt_nest;


/**
 * @brief This function will be invoked by BSP, when enter interrupt service routine.
 *
 * @note Please don't invoke this routine in application.
 *
 * @see rt_interrupt_leave
 */
void rt_interrupt_enter(void)
{
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    rt_interrupt_nest++;
    rt_hw_interrupt_enable(level);
}

/**
 * @brief This function will be invoked by BSP, when leave interrupt service routine.
 *
 * @note Please don't invoke this routine in application.
 *
 * @see rt_interrupt_enter
 */
void rt_interrupt_leave(void)
{
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    rt_interrupt_nest--;
    rt_hw_interrupt_enable(level);
}
