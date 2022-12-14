

#include "bmp180.h"
#include "bmp180_sample.h"

/*
 * Copyright (c) 2020 panrui <https://github.com/Prry/rtt-bmp180>
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-03-12     panrui      the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "sensor.h"
#include "bsp_api.h"
rt_device_t baro_dev = RT_NULL, temp_dev = RT_NULL;
struct rt_sensor_data baro_data,temp_data;
rt_size_t res0 = 0, res1 = 1;
rt_uint8_t chip_id;
void read_baro_entry(void)
{
    baro_dev = rt_device_find("baro_bmp180");
    if (baro_dev == RT_NULL)
    {
         rt_kprintf("not found baro_bmp180 device\r\n");
        return;
    }

    if (rt_device_open(baro_dev, RT_DEVICE_FLAG_RDONLY) != RT_EOK)
    {
        rt_kprintf("open baro_180 failed\r\n");
        return;
    }

    temp_dev = rt_device_find("temp_bmp180");
    if (temp_dev == RT_NULL)
    {
         rt_kprintf("not found temp_bmp180 device\r\n");
        return;
    }

    if (rt_device_open(temp_dev, RT_DEVICE_FLAG_RDONLY) != RT_EOK)
    {
        rt_kprintf("open temp_bmp180 failed\r\n");
        return;
    }

    rt_device_control(baro_dev, RT_SENSOR_CTRL_SET_ODR, (void *)(1));/* 1Hz read */
    rt_device_control(temp_dev, RT_SENSOR_CTRL_SET_ODR, (void *)(1));/* 1Hz read */

    rt_device_control(temp_dev, RT_SENSOR_CTRL_GET_ID, (void*)&chip_id);
    rt_kprintf("bmp180 chip ID [0x%X]\n", chip_id);
}
unsigned char *bmp_read(void)
{
    static unsigned char bmp[2];
    res0 = rt_device_read(baro_dev, 0, &baro_data, 1);
    res0 = rt_device_read(temp_dev, 0, &temp_data, 1);
    if (res0==0 || res1==0)
    {
        rt_kprintf("read data failed! result is %d,%d\n", res0, res1);
        rt_device_close(baro_dev);
        rt_device_close(temp_dev);
    }
    bmp[0]=baro_data.data.baro/1000;
    bmp[1]=temp_data.data.temp/10-44;
    rt_kprintf("baro[%dPa],temp[%d.%dC],timestamp[%d]\r\n", baro_data.data.baro,
               temp_data.data.temp/10-44, temp_data.data.temp%10,
               temp_data.timestamp);
    return bmp;
}


int rt_hw_bmp180_port(void)
{
    struct rt_sensor_config cfg;

    cfg.intf.dev_name = "i2c1";         /* i2c bus */
    cfg.intf.user_data = (void *)0x77;  /* i2c slave addr */
    rt_hw_bmp180_init("bmp180", &cfg);  /* bmp180 */
    read_baro_entry();
    return RT_EOK;
}
INIT_COMPONENT_EXPORT(rt_hw_bmp180_port);

