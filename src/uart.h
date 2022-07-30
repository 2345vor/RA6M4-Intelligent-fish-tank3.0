/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-07-25     Asus       the first version
 */
#ifndef _UART_H_
#define _UART_H_

#include "hal_data.h"
#include <rtthread.h>
#include <rtdevice.h>
#include <stdio.h>
#include <string.h>
#include "pwmled.h"
#include "adc.h"
#include "bmp180_sample.h"
#include "dhtxx_sample.h"
//static rt_err_t uart_rx_ind(rt_device_t dev, rt_size_t size);
//static char uart_sample_get_char(void);
//static void control_thread_entry(void);
void serial_thread_entry(rt_uint8_t a,rt_uint8_t b);
//static int uart_data_sample(int argc, char *argv[]);
#endif /* SRC_UART_H_ */
