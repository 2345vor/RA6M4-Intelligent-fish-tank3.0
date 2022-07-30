/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-07-11     Asus       the first version
 */
/*
 * 程序清单：这是一个 PWM 设备使用例程
 * 例程导出了 pwm_led_sample 命令到控制终端
 * 命令调用格式：pwm_led_sample
 * 程序功能：通过 PWM 设备控制 LED 灯的亮度，可以看到LED不停的由暗变到亮，然后又从亮变到暗。
*/
#include "pwmled.h"

#define PWM_DEV_NAME        "pwm8"  /* PWM设备UV灯名称 */
#define PWM2_DEV_NAME       "pwm7"  /* PWM设备水泵名称 */
#define PWM_DEV_CHANNEL      0   /* PWM通道 */
#define period             500000    /* 周期为0.5ms，单位为纳秒us */
struct rt_device_pwm *pwm_dev;      /* PWM设备句柄 */
struct rt_device_pwm *pwm2_dev;      /* PWM2设备句柄 */
int pwm_Initiation(void)
{
    rt_err_t rt_err = RT_EOK;
    rt_uint16_t pulse = 0;  /* 初始使能为零 */

    /* 查找UV灯设备 */
    pwm_dev = (struct rt_device_pwm *)rt_device_find(PWM_DEV_NAME);
    if (pwm_dev == RT_NULL)
    {
        rt_kprintf("pwm sample run failed! can't find %s device!\n", PWM_DEV_NAME);
        rt_err = RT_NULL;
    }
    else {
        rt_kprintf("rt_sensor find %s device init success!\n", PWM_DEV_NAME);
    }
    /* 查找水泵设备 */
    pwm2_dev = (struct rt_device_pwm *)rt_device_find(PWM2_DEV_NAME);
    if (pwm2_dev == RT_NULL)
    {
        rt_kprintf("pwm sample run failed! can't find %s device!\n", PWM2_DEV_NAME);
        rt_err = RT_NULL;
    }
    else {
        rt_kprintf("rt_sensor find %s device init success!\n", PWM2_DEV_NAME);
    }
    /* 设置PWM周期和脉冲宽度默认值 */
    rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, pulse);
    rt_pwm_set(pwm2_dev, PWM_DEV_CHANNEL, period, pulse);
    /* 使能设备 */
    rt_pwm_enable(pwm_dev, PWM_DEV_CHANNEL);
    rt_pwm_enable(pwm2_dev, PWM_DEV_CHANNEL);
    return rt_err;
}
/*a,b范围在0~10*/
void pwm_action(rt_uint8_t a,rt_uint8_t b)
{

    if (a>=10) {
        a=10;
    }
    else if (a<=0) {
        a=0;
    }
    if (b>=10) {
        b=10;
    }
    else if (b<=5) {
        b=0;
    }
    if (a==0&&b==0) {
        rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, 0);//UV灯
        rt_pwm_set(pwm2_dev, PWM_DEV_CHANNEL, period, 0);//水泵
    } else {
        rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, period*0.1*a);//UV灯
        rt_pwm_set(pwm2_dev, PWM_DEV_CHANNEL, period, period*0.7+period*0.03*b);//水泵
    }
}
INIT_APP_EXPORT(pwm_Initiation);
