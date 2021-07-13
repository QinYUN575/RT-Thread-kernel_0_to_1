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
