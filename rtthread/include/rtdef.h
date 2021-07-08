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

#ifdef __cplusplus
extern "C"
{
#endif

/* RT-Thread basic data type definitions */
typedef signed char         rt_int8_t;
typedef signed short        rt_int16_t;
typedef signed int          rt_int32_t;
typedef unsigned char       rt_uint8_t;
typedef unsigned short      rt_uint16_t;
typedef unsigned int        rt_uint32_t;
typedef int                 rt_bool_t;

typedef long                rt_base_t;
typedef unsigned long       rt_ubase_t;

typedef rt_base_t           rt_err_t;
typedef rt_uint32_t         rt_time_t;
typedef rt_uint32_t         rt_tick_t;
typedef rt_base_t           rt_flag_t;
typedef rt_ubase_t          rt_size_t;
typedef rt_ubase_t          rt_dev_t;
typedef rt_base_t           rt_off_t;

/* boolean type definitions */
#define RT_TRUE             1
#define RT_FALSE            0


#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
#define __CLANG_ARM
#endif

/* Compiler Related Definitions */
#if defined(__CC_ARM) || defined(__CLANG_ARM) /* ARM Compiler */
#define rt_inline           static __inline
#define ALIGN(n)            __attribute__((aligned(n)))

#elif defined(__IAR_SYSTEMS_ICC__)
#define rt_inline           static inline
#define ALIGN(n)            PRAGMA(data_alignment = n)

#elif defined(__GNUC__)
#define rt_inline           static __inline
#define ALIGN(n)            __attribute__((aligned(n)))

#else
#error not supported tool chain
#endif

/* RT-Thread error code definitions */
#define RT_EOK              0   /**< There is no error */
#define RT_ERROR            1   /**< A generic error happens */
#define RT_ETIMEOUT         2   /**< Timed out */
#define RT_EFULL            3   /**< The resource is full */
#define RT_EEMPTY           4   /**< The resource is empty */
#define RT_ENOMEM           5   /**< No memory */
#define RT_ENOSYS           6   /**< No system */
#define RT_EBUSY            7   /**< Busy */
#define RT_EIO              8   /**< IO error */
#define RT_EINTR            9   /**< interrupted system call */
#define RT_EINVAL           10  /**< Inval argument */


#define RT_ALIGN(size, align)           (((size) + (align)-1) & ~((align)-1))
#define RT_ALIGN_DOWN(size, align)      ((size) & ~((align)-1))

#define RT_NULL                         (0)


/**
 * Double List structure
 */
struct rt_list_node
{
    struct rt_list_node *next;
    struct rt_list_node *prev;
};
typedef struct rt_list_node rt_list_t;

/**
 * Thread structure
 */
struct rt_thread
{
    rt_list_t tlist; /**< the thread list */

    /* stack point and entry */
    void *sp;               /**< stack point */
    void *entry;            /**< entry */
    void *parameter;        /**< parameter */
    void *stack_addr;       /**< stack address */
    rt_uint32_t stack_size; /**< stack size */
};
typedef struct rt_thread *rt_thread_t;

#ifdef __cplusplus
}
#endif

#endif /* __RT_DEF_H__ */
