/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-07-11     Asus       the first version
 */
#ifndef _PWMLED_H_
#define _PWMLED_H_
#include <rtthread.h>
#include "hal_data.h"
#include <rtdevice.h>

int pwm_Initiation(void);
void pwm_action(rt_uint8_t a,rt_uint8_t b);

#endif /* _PWMLED_H_ */
