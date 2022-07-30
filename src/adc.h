/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-07-24     Asus       the first version
 */

#ifndef _ADC_H_
#define _ADC_H_
#include <rtthread.h>
#include <rtdevice.h>
#include <stdio.h>
#include <stdlib.h>
int adc_Initiation(void);
rt_uint8_t *adc_read();

#endif /* _ADC_H_ */

