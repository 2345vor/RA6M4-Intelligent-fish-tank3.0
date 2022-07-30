/*
#include <pwmled.h>
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2021-10-10     Sherman       first version
 * 2021-11-03     Sherman       Add icu_sample
 */

#include <rtthread.h>
#include "hal_data.h"
#include <rtdevice.h>
#include <stdio.h>
#include <string.h>
#include "pwmled.h"
#include "adc.h"
#include "uart.h"

/*a,b范围在0~10*/
rt_uint8_t a = 0,b = 0;


void hal_entry(void)
{

//    void pwm_Initiation(void);

    rt_kprintf("\nHello RT-Thread!\n");

    while (1)
    {
//        pwm_action( a, b);
//        adc_read();
//        strcpy(adc_value,adc_read());    //正确，使用标准库函数可实现字符串拷贝
//        rt_kprintf(adc_value);
        serial_thread_entry(a,b);
        rt_thread_mdelay(500);
    }
}






