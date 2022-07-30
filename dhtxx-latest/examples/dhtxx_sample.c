/*
 * Copyright (c) 2020, RudyLo <luhuadong@163.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-01-20     luhuadong    the first version
 * 2020-10-05     luhuadong    v0.9.0
 */
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "dhtxx_sample.h"
#include "dhtxx.h"
#include "bsp_api.h"
#include <stdio.h>
#include <string.h>

#define DATA_PIN     BSP_IO_PORT_01_PIN_02//dht温湿度端口定义

/* cat_dhtxx sensor data by dynamic */
rt_uint8_t *cat_dhtxx(void)
{
    static rt_uint8_t dht[2];
    dht_device_t sensor = dht_create(DATA_PIN);
    if(dht_read(sensor)) {
        rt_int32_t temp = dht_get_temperature(sensor);
        rt_int32_t humi = dht_get_humidity(sensor);
        rt_kprintf("Temp: %d.%d 'C,  Humi: %d '% \n", temp/10-2, temp%10, humi/10);
        dht[0] = temp/10-4,dht[1] = humi/10;
    }
    else {
        rt_kprintf("Read dht sensor failed.\n");
    }
    rt_thread_mdelay(100);
    dht_delete(sensor);
    return dht;
}

//#ifdef FINSH_USING_MSH
//MSH_CMD_EXPORT(cat_dhtxx, read dhtxx humidity and temperature);
//#endif
