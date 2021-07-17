/**
 * @file object.c
 * @author TsMax (QinYUN575@Foxmail.com)
 * @brief
 * @version 0.1
 * @date 2021-07-12
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <rthw.h>
#include <rtthread.h>

/**
 * Define object_info for the number of rt_object_container items.
 */
enum rt_object_info_type
{
    RT_Object_Info_Thread = 0,      /**< The object is thread. */
#ifdef RT_USING_SEMAPHORE
    RT_Object_Info_Semaphore,       /**< The object is semaphore. */
#endif
#ifdef RT_USING_MUTEX
    RT_Object_Info_Mutex,           /**< The object is mutex. */
#endif
#ifdef RT_USING_EVENT
    RT_Object_Info_Event,           /**< The object is event. */
#endif
#ifdef RT_USING_MAILBOX
    RT_Object_Info_MailBox,         /**< The object is mail box. */
#endif
#ifdef RT_USING_MESSAGEQUEUE
    RT_Object_Info_MessageQueue,    /**< The object is message queue. */
#endif
#ifdef RT_USING_MEMHEAP
    RT_Object_Info_MemHeap,         /**< The object is memory heap. */
#endif
#ifdef RT_USING_MEMPOOL
    RT_Object_Info_MemPool,         /**< The object is memory pool. */
#endif
#ifdef RT_USING_DEVICE
    RT_Object_Info_Device,          /**< The object is device */
#endif
    RT_Object_Info_Timer,           /**< The object is timer. */
    RT_Object_Info_Unknown,         /**< The object is unknown. */
};

#define _OBJ_CONTAINER_LIST_INIT(c) \
    {&(rt_object_container[c].object_list), &(rt_object_container[c].object_list)}
static struct rt_object_information rt_object_container[RT_Object_Info_Unknown] =
{
    /* initialize object container - thread. */
    {RT_Object_Class_Thread,         _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_Thread),        sizeof(struct rt_thread)},
#ifdef RT_USING_SEMAPHORE
    /* initialize object container - semaphore. */
    {RT_Object_Class_Semaphore,      _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_Semaphore),     sizeof(struct rt_semaphore)},
#endif
#ifdef RT_USING_MUTEX
    /* initialize object container - mutex. */
    {RT_Object_Class_Mutex,          _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_Mutex),         sizeof(struct rt_mutex)},
#endif
#ifdef RT_USING_EVENT
    /* initialize object container - event. */
    {RT_Object_Class_Event,          _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_Event),         sizeof(struct rt_event)},
#endif
#ifdef RT_USING_MAILBOX
    /* initialize object container - mail box. */
    {RT_Object_Class_Mailbox,        _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_MailBox),       sizeof(struct rt_mailbox)},
#endif
#ifdef RT_USING_MESSAGEQUEUE
    /* initialize object container - message queue. */
    {RT_Object_Class_MessageQueue,   _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_MessageQueue),  sizeof(struct rt_messagequeue)},
#endif
#ifdef RT_USING_MEMHEAP
    /* initialize object container - memory heap. */
    {RT_Object_Class_Memheap,        _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_MemHeap),       sizeof(struct rt_memheap)},
#endif
#ifdef RT_USING_MEMPOOL
    /* initialize object container - memory pool. */
    {RT_Object_Class_MemPool,        _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_MemPool),       sizeof(struct rt_mempool)},
#endif
#ifdef RT_USING_DEVICE
    /* initialize object container - device. */
    {RT_Object_Class_Device,         _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_Device),        sizeof(struct rt_device)},
#endif
    /* initialize object container - timer. */
    {RT_Object_Class_Timer,          _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_Timer),         sizeof(struct rt_timer)},
};


/**
 * @brief The function will return the specified type of object information.
 *
 * @param type the type of object, which can be
 *              RT_Object_Class_Thread/Semaphore/Mutex ... etc.
 *
 * @return the object type information or RT_NULL.
 */
struct rt_object_information *rt_object_get_information(enum rt_object_class_type type)
{
    int index;

    for (index = 0; index < RT_Object_Info_Unknown; index++)
    {
        if (rt_object_container[index].type == type)
        {
            return &rt_object_container[index];
        }
    }
    return RT_NULL;
}


/**
 * @brief This function will initialize an object and add it to object system
 *          management.
 *
 * @param object the specified object to be initialized.
 * @param type the object type.
 * @param name the object name. In system, the object's name must be unique.
 */
void rt_object_init(struct rt_object            *object,
                    enum rt_object_class_type   type,
                    const char                  *name)
{
    register rt_base_t temp;
    struct rt_list_node *node = RT_NULL;
    struct rt_object_information *information;

    /* get object information */
    information = rt_object_get_information(type);

    /* check object type to avoid re-initialization */

    // /* enter critical */
    // rt_enter_critical();
    // /* try to find object */
    // for (node = information->object_list.next;
    //         node != &(information->object_list);
    //         node = node->next)
    // {
    //     struct rt_object *obj;
    //     obj = rt_list_entry(node, struct rt_object, list);

    //     /**
    //      * @TODO:
    //      *
    //      */
    //     // if (obj)
    //     // {

    //     // }
    // }
    // /* leave critical */
    // rt_exit_critical();

    /* initialize object's paramter */
    /* set object type to static */
    object->type = type | RT_Object_Class_Static;
    /* copy name */
    rt_strncpy(object->name, name,  RT_NAME_MAX);

    /* lock interrupt */
    temp = rt_hw_interrupt_disable();
    /* insert object into information object list */
    rt_list_insert_after(&(information->object_list), &(object->list));
    /* unlock interrupt */
    rt_hw_interrupt_enable(temp);
}
