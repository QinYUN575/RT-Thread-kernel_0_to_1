/**
 * @file kservice.c
 * @author TsMax (QinYUN575@Foxmail.com)
 * @brief
 * @version 0.1
 * @date 2021-07-13
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <rtthread.h>
#include <rthw.h>


/**
 * @brief the function will copy string no more than n bytes.
 *
 * @param dst the string to copy
 * @param str the string to be copied
 * @param n the maximum copied length
 * @return the result
 */
char *rt_strncpy(char *dst, const char *src, rt_ubase_t n)
{
    if (n != 0)
    {
        char *d = dst;
        const char *s = src;

        do
        {
            if ((*d++ = *s++) == 0)
            {
                /* NUL pad the remaining n-1 bytes */
                while (--n != 0)
                    *d++ = 0;
                break;
            }
        } while (--n != 0);
    }

    return (dst);
}

#if RT_USING_CPU_FFS
const rt_uint8_t __lowest_bit_bitmap[] = {
    0, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, /**< 0x00 */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, /**< 0x10 */
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, /**< 0x20 */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, /**< 0x30 */
    6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, /**< 0x40 */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, /**< 0x50 */
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, /**< 0x60 */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, /**< 0x70 */
    7, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, /**< 0x80 */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, /**< 0x90 */
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, /**< 0xA0 */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, /**< 0xB0 */
    6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, /**< 0xC0 */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, /**< 0xD0 */
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, /**< 0xE0 */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, /**< 0xF0 */
};

/**
 * @brief This function finds the first bit set (beginning with the last significant bit)
 * in value and return the index of that bit.
 * 
 * Bits are numbered starting at (the laster significant bit). A return value of
 * zero from any of these functions means that the argument was zero.
 * 
 * @param value 
 * @return return the index of the fist bit set. If value is 0, then this function
 * shall return 0. 
 */
int __rt_ffs(int value)
{
    if (value == 0)
        return 0;
    if (value & 0xff)
        return __lowest_bit_bitmap[value & 0xff] + 1;
    if (value & 0xff00)
        return __lowest_bit_bitmap[(value & 0xff00) >> 8] + 9;
    if (value & 0xff0000)
        return __lowest_bit_bitmap[(value & 0xff0000) >> 16] + 17;

    return __lowest_bit_bitmap[(value & 0xff000000) >> 24] + 25;
}
#endif