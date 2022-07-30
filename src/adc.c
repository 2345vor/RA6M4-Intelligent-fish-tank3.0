/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-07-11     Asus       the first version
 */

#include"adc.h"
#define ADC_NAME        "adc0"  /* ADC 设 备 名 称 */
#define LM35_ADC_CHANNEL       0     /* LM35_ADC水体温度通 道 */
#define light_ADC_CHANNEL       1     /* light_ADC光敏通 道 */
#define REFER_VOLTAGE    330    /* 参 考 电 压 3.3V,数 据 精 度 乘 以100保 留2位 小 数*/
#define CONVERT_BITS (1 << 12) /* 转 换 位 数 为12位 */
rt_adc_device_t adc_dev;        /* adc设备句柄 */
rt_err_t ret = RT_EOK;
int adc_Initiation(void)
{
    rt_err_t ret = RT_EOK;
    /* 查 找 设 备 */
    adc_dev = (rt_adc_device_t)rt_device_find(ADC_NAME);
    if (adc_dev == RT_NULL)
    {
        rt_kprintf("adc sample run failed! can't find %s device!\n", ADC_NAME);
        ret = RT_ERROR;
    }
    else
    {
        rt_kprintf("rt_sensor find %s device init success!\n", ADC_NAME);
    }

    return ret;
}
rt_uint8_t *adc_read()
{
    rt_int16_t LM35=0,light=0;
    static rt_uint8_t adc[2], adc_value[4], max = 5;
    for (int var = 0; var < max; ++var) {
        /* 使 能 设 备 */
        ret = rt_adc_enable(adc_dev, LM35_ADC_CHANNEL);
        ret = rt_adc_enable(adc_dev, light_ADC_CHANNEL);
        rt_thread_mdelay(var);
        /* 1读 取 采 样 值 */
        LM35 = LM35+ rt_adc_read(adc_dev, LM35_ADC_CHANNEL);
        rt_thread_mdelay(var);
        /* 2读 取 采 样 值 */
        light = light + rt_adc_read(adc_dev, light_ADC_CHANNEL);
        /* 关 闭 通 道 */
        ret = rt_adc_disable(adc_dev, LM35_ADC_CHANNEL);
        ret = rt_adc_disable(adc_dev, light_ADC_CHANNEL);
        rt_thread_mdelay(50);
    }
    LM35 = LM35/max,light = light/max;
//    rt_kprintf("the LM35 is :%d \n", LM35);
    /* 转 换 为 对 应 温 度 值 */
    LM35 = LM35*(REFER_VOLTAGE/40.96); //转化为温度
    adc_value[0] = LM35 / 100-22;
    adc_value[1] = LM35 % 100;
    rt_kprintf("the voltage is :%d.%02d `C\n", adc_value[0], adc_value[1]);
//    rt_kprintf("the light is :%d \n", light);
    /* 转 换 为 对 应 电 压 值 */
    light = light * REFER_VOLTAGE / CONVERT_BITS;
    adc_value[2] = light /100;
    adc_value[3] = light %100;
    rt_kprintf("the voltage is :%d.%02d lx\n", adc_value[2], adc_value[3]);
    adc[0] = LM35/100-22;
    adc[1] = light;
    return adc;
}

INIT_APP_EXPORT(adc_Initiation);



