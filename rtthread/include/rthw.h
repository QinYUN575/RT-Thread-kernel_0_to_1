/**
 * @file rthw.h
 * @author TsMax (QinYUN575@Foxmail.com)
 * @brief
 * @version 0.1
 * @date 2021-07-06
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef __RT_HW_H__
#define __RT_HW_H__

#include <rtdef.h>
#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * CPU interfaces
 */
rt_uint8_t *rt_hw_stack_init(void *tentry,
                             void *parameter,
                             rt_uint8_t *stack_addr);

/**
 * Context interfaces
 */
void rt_hw_context_switch(rt_ubase_t from, rt_ubase_t to);
void rt_hw_context_switch_to(rt_ubase_t to);


rt_base_t rt_hw_interrupt_disable(void);
void rt_hw_interrupt_enable(rt_base_t level);

#ifdef __cplusplus
}
#endif

#endif
