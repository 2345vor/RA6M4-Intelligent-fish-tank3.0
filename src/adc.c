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
#define ADC_NAME        "adc0"  /* ADC �� �� �� �� */
#define LM35_ADC_CHANNEL       0     /* LM35_ADCˮ���¶�ͨ �� */
#define light_ADC_CHANNEL       1     /* light_ADC����ͨ �� */
#define REFER_VOLTAGE    330    /* �� �� �� ѹ 3.3V,�� �� �� �� �� ��100�� ��2λ С ��*/
#define CONVERT_BITS (1 << 12) /* ת �� λ �� Ϊ12λ */
rt_adc_device_t adc_dev;        /* adc�豸��� */
rt_err_t ret = RT_EOK;
int adc_Initiation(void)
{
    rt_err_t ret = RT_EOK;
    /* �� �� �� �� */
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
        /* ʹ �� �� �� */
        ret = rt_adc_enable(adc_dev, LM35_ADC_CHANNEL);
        ret = rt_adc_enable(adc_dev, light_ADC_CHANNEL);
        rt_thread_mdelay(var);
        /* 1�� ȡ �� �� ֵ */
        LM35 = LM35+ rt_adc_read(adc_dev, LM35_ADC_CHANNEL);
        rt_thread_mdelay(var);
        /* 2�� ȡ �� �� ֵ */
        light = light + rt_adc_read(adc_dev, light_ADC_CHANNEL);
        /* �� �� ͨ �� */
        ret = rt_adc_disable(adc_dev, LM35_ADC_CHANNEL);
        ret = rt_adc_disable(adc_dev, light_ADC_CHANNEL);
        rt_thread_mdelay(50);
    }
    LM35 = LM35/max,light = light/max;
//    rt_kprintf("the LM35 is :%d \n", LM35);
    /* ת �� Ϊ �� Ӧ �� �� ֵ */
    LM35 = LM35*(REFER_VOLTAGE/40.96); //ת��Ϊ�¶�
    adc_value[0] = LM35 / 100-22;
    adc_value[1] = LM35 % 100;
    rt_kprintf("the voltage is :%d.%02d `C\n", adc_value[0], adc_value[1]);
//    rt_kprintf("the light is :%d \n", light);
    /* ת �� Ϊ �� Ӧ �� ѹ ֵ */
    light = light * REFER_VOLTAGE / CONVERT_BITS;
    adc_value[2] = light /100;
    adc_value[3] = light %100;
    rt_kprintf("the voltage is :%d.%02d lx\n", adc_value[2], adc_value[3]);
    adc[0] = LM35/100-22;
    adc[1] = light;
    return adc;
}

INIT_APP_EXPORT(adc_Initiation);



