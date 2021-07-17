#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   gettab.py
@Time    :   2021/07/17 13:51:34
@Author  :   TsMax
@Version :   1.0
@Contact :   qinyun575#foxmail.com
@Desc    :   None
'''

# here put the import lib
sample = 256


def getlowbit(byte):
    c = 0
    for i in range(0, 8):
        if (byte & 0x01):
            return c
        c = c + 1
        byte = byte >> 1
    return 0


line = ""

for i in range(0, sample):
    print("%d," % getlowbit(i))
    if ((i+1) % 16 == 0):
        print("\n")
