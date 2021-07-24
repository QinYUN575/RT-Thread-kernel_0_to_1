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

/**
 * @ingroup BasicDef
 *
 * @def RT_ALIGN(size, align)
 * Return the most contiguous size aligned at specified width.
 * RT_ALIGN(13, 4) would return 16.
 *
 */
#define RT_ALIGN(size, align)           (((size) + (align)-1) & ~((align)-1))

/**
 * @ingroup BasicDef
 *
 * @def RT_ALIGN_DOWN(size, align)
 * Return the down number of aligned at specified width.
 * RT_ALIGN_DOWN(13, 4) would return 12.
 *
 */
#define RT_ALIGN_DOWN(size, align)      ((size) & ~((align)-1))

/**
 * @ingroup BasicDef
 *
 * @def RT_NULL
 * Similar as the NULL in C library.
 */
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
 * Kernel object macros
 */

/**
 * Base structure of Kernel object
 */
struct rt_object
{
    char name[RT_NAME_MAX]; /**< name of kernel object */
    rt_uint8_t type;        /**< type of kernel object */
    rt_uint8_t flag;        /**< flag of kernel object */

    rt_list_t list;         /**< list node of kernel object */
};
typedef struct rt_object *rt_object_t;  /**< Type for kernel objects. */

/**
 * The object type can be one of the follows with specific
 * macros enabled:
 * - Thread
 * - Semaphore
 * - Mutex
 * - Event
 * - MailBox
 * - MessageQueue
 * - MemHeap
 * - MemPool
 * - Device
 * - Timer
 * - UnKnown
 * - Static
 */
enum rt_object_class_type
{
    RT_Object_Class_Null            = 0x00,     /**< The object is not used. */
    RT_Object_Class_Thread          = 0x01,     /**< The object is a thread. */
    RT_Object_Class_Semaphore       = 0x02,     /**< The object is a semaphore. */
    RT_Object_Class_Mutex           = 0x03,     /**< The object is a mutex. */
    RT_Object_Class_Event           = 0x04,     /**< The object is a event. */
    RT_Object_Class_MailBox         = 0x05,     /**< The object is a mail box. */
    RT_Object_Class_MessageQueue    = 0x06,     /**< The object is a message queue. */
    RT_Object_Class_MemHeap         = 0x07,     /**< The object is a memory heap. */
    RT_Object_Class_MemPool         = 0x08,     /**< The object is a memory pool. */
    RT_Object_Class_Device          = 0x09,     /**< The object is a device. */
    RT_Object_Class_Timer           = 0x0A,     /**< The object is a timer. */
    RT_Object_Class_Unknown         = 0x0B,     /**< The object is unknown. */
    RT_Object_Class_Static          = 0x80      /**< The object is a static object. */
};

/**
 * The information of the kernel object
 */
struct rt_object_information
{
    enum rt_object_class_type type; /**< object class type */
    rt_list_t   object_list;        /**< object list */
    rt_size_t   object_size;        /**< object size */
};

#ifndef RT_TIMER_SKIP_LIST_LEVEL
    #define RT_TIMER_SKIP_LIST_LEVEL    1
#endif

/* 1 or 3 */
#ifndef RT_TIMER_SKIP_LIST_MASK
    #define RT_TIMER_SKIP_LIST_MASK     0x03
#endif


/**
 * Timer structure
 */
struct rt_timer
{
    struct rt_object parent;
    rt_list_t row[RT_TIMER_SKIP_LIST_LEVEL];
    void (*timeout_func)(void *parameter);
    void *parameter;
    rt_tick_t init_tick;
    rt_tick_t timeout_tick;
};
typedef struct rt_timer *rt_timer_t;

#define RT_TICK_MAX                 0xFFFFFFFF

#define RT_TIMER_FLAG_DEACTIVATED   0x0
#define RT_TIMER_FLAG_ACTIVATED     0x1
#define RT_TIMER_FLAG_ONE_SHOT      0x0
#define RT_TIMER_FLAG_PERIODIC      0x3

#define RT_TIMER_FLAG_HARD_TIMER    0x0
#define RT_TIMER_FLAG_SOFT_TIMER    0x4

#define RT_TIMER_CTRL_SET_TIME      0x0
#define RT_TIMER_CTRL_GET_TIME      0x1
#define RT_TIMER_CTRL_SET_ONESHOT   0x2
#define RT_TIMER_CTRL_SET_PERIODIC  0x3


/**
 * Thread state definitions
 */
#define RT_THREAD_INIT                  0x00                /**< Initialized status */
#define RT_THREAD_READY                 0x01                /**< Ready status */
#define RT_THREAD_SUSPEND               0x02                /**< Suspend status */
#define RT_THREAD_RUNNING               0x03                /**< Running status */
#define RT_THREAD_BLOCK                 RT_THREAD_SUSPEND   /**< Blocked status */
#define RT_THREAD_CLOSE                 0x04                /**< Closed status */

#define RT_THREAD_STAT_MASK             0x0f
#define RT_THREAD_STAT_SIGNAL           0x10
#define RT_THREAD_STAT_SIGNAL_READY     (RT_THREAD_STAT_SIGNAL | RT_THREAD_READY)
#define RT_THREAD_STAT_SIGNAL_SUSPEND   0x20
#define RT_THREAD_STAT_SIGNAL_MASK      0xf0

/**
 * Thread structure
 */
struct rt_thread
{
    char name[RT_NAME_MAX];         /**< name of kernel object */
    rt_uint8_t type;                /**< type of kernel object */
    rt_uint8_t flags;               /**< flags of kernel object */
    rt_list_t list;                 /**< list node of kernel object */

    rt_list_t tlist;                /**< the thread list */

    /* stack point and entry */
    void *sp;                       /**< stack point */
    void *entry;                    /**< entry */
    void *parameter;                /**< parameter */
    void *stack_addr;               /**< stack address */
    rt_uint32_t stack_size;         /**< stack size */

    rt_ubase_t remaining_tick;      /**< remaining tick */

    rt_uint8_t current_priority;    /**< current priority*/
    rt_uint8_t init_priority;       /**< initialized priority */
    rt_uint32_t number_mask;        /**< number mask of thread priority */

    rt_err_t error;                 /**< error code */
    rt_uint8_t stat;                /**< state of thread */

    struct rt_timer thread_timer;   /**< timer of thread */
};
typedef struct rt_thread *rt_thread_t;

#ifdef __cplusplus
}
#endif

#endif /* __RT_DEF_H__ */
