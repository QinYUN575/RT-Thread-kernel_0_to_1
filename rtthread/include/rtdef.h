/**
 * @file rtdef.h
 * @author TsMax (QinYUN575@Foxmail.com)
 * @brief
 * @version 0.1
 * @date 2021-07-02
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef __RT_DEF_H__
#define __RT_DEF_H__

/* include rtconfig header to import configuration */
#include <rtconfig.h>

/* RT-Thread basic data type definitions */
typedef signed char             rt_int8_t;
typedef signed short            rt_int16_t;
typedef signed long             rt_int32_t;
typedef unsigned char           rt_uint8_t;
typedef unsigned short          rt_uint16_t;
typedef unsigned long           rt_uint32_t;
typedef int                     rt_bool_t;

/* 32Bit CPU */
typedef long                    rt_base_t;
typedef unsigned long           rt_ubase_t;

typedef rt_base_t               rt_err_t;
typedef rt_uint32_t             rt_time_t;
typedef rt_uint32_t             rt_tick_t;
typedef rt_base_t               rt_flag_t;
typedef rt_ubase_t              rt_size_t;
typedef rt_ubase_t              rt_dev_t;
typedef rt_base_t               rt_off_t;

/* boolean type definitions */
#define RT_TRUE 1
#define RT_FALSE 0

#ifdef __CC_ARM
#define rt_inline                       static __inline
#define ALIGN(n)                        __attribute__((aligned(n)))

#elif defined(__IAR_SYSTEMS_ICC__)
#define rt_inline                       static inline
#define ALIGN(n)                        PRGMA(data_alignment = n)

#elif defined(__GNUC__)
#define rt_inline                       static __inline
#define ALIGN(n)                        __attribute__((aligned(n)))

#else
#error not supported tool chain
#endif

#define RT_ALIGN(size, align)           (((size) + (align)-1) & ~((align)-1))
#define RT_ALIGN_DOWN(size, align)      ((size) & ~((align)-1))

#define RT_NULL                         (0)

#endif /* __RT_DEF_H__ */