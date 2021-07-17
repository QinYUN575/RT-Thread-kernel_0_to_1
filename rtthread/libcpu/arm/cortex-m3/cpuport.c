/**
 * @file cpuport.c
 * @author TsMax (QinYUN575@Foxmail.com)
 * @brief
 * @version 0.1
 * @date 2021-07-02
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <rtthread.h>

struct exception_stack_frame
{
    rt_uint32_t r0;
    rt_uint32_t r1;
    rt_uint32_t r2;
    rt_uint32_t r3;

    rt_uint32_t r12;
    rt_uint32_t lr;
    rt_uint32_t pc;
    rt_uint32_t psr;
};

struct stack_frame
{
    /* r4 ~ r11 register */
    rt_uint32_t r4;
    rt_uint32_t r5;
    rt_uint32_t r6;
    rt_uint32_t r7;
    rt_uint32_t r8;
    rt_uint32_t r9;
    rt_uint32_t r10;
    rt_uint32_t r11;

    struct exception_stack_frame exception_stack_frame;
};

/* flag in interrupt handling */
rt_uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;

/**
 * @brief This function will initialize thread stack
 *
 * @param tentry the entry of thread
 * @param parameter the parameter of entry
 * @param stack_addr the beginning stack address
 * @return stack address
 */
rt_uint8_t *rt_hw_stack_init(void *tentry,
                             void *parameter,
                             rt_uint8_t *stack_addr)
{
    struct stack_frame *stack_frame;
    rt_uint8_t *stk;
    unsigned long i;

    stk = stack_addr + sizeof(rt_uint32_t);

    stk = (rt_uint8_t *)RT_ALIGN_DOWN((rt_uint32_t)stk, 8);
    stk -= sizeof(struct stack_frame);
    stack_frame = (struct stack_frame *)stk;

    /* init all register */
    for (i = 0; i < sizeof(struct stack_frame) / sizeof(rt_uint32_t); i++)
    {
        ((rt_uint32_t *)stack_frame)[i] = 0xdeadbeef;
    }

    stack_frame->exception_stack_frame.r0 = (unsigned long)parameter;   /* r0: argument */
    stack_frame->exception_stack_frame.r1 = 0;                          /* r1 */
    stack_frame->exception_stack_frame.r2 = 0;                          /* r2 */
    stack_frame->exception_stack_frame.r3 = 0;                          /* r3 */
    stack_frame->exception_stack_frame.r12 = 0;                         /* r12 */
    stack_frame->exception_stack_frame.lr = 0;                          /* lr */
    stack_frame->exception_stack_frame.pc = (unsigned long)tentry;      /* entry pointer, pc */
    stack_frame->exception_stack_frame.psr = 0x01000000L;               /* PSR */

    return stk;
}

#ifdef RT_USING_CPU_FFS
#if defined(__CC_ARM)
__asm int __rt_ffs(int value)
{
    CMP     r0, #0x00
    BEQ     exit

    RBIT    r0, r0
    CLZ     r0, r0
    ADDS    r0, r0, #0x01

exit
    BX      lr
}
#endif
#endif
