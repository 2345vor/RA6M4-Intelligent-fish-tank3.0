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
 * �����嵥������һ�� PWM �豸ʹ������
 * ���̵����� pwm_led_sample ��������ն�
 * ������ø�ʽ��pwm_led_sample
 * �����ܣ�ͨ�� PWM �豸���� LED �Ƶ����ȣ����Կ���LED��ͣ���ɰ��䵽����Ȼ���ִ����䵽����
*/
#include "pwmled.h"

#define PWM_DEV_NAME        "pwm8"  /* PWM�豸UV������ */
#define PWM2_DEV_NAME       "pwm7"  /* PWM�豸ˮ������ */
#define PWM_DEV_CHANNEL      0   /* PWMͨ�� */
#define period             500000    /* ����Ϊ0.5ms����λΪ����us */
struct rt_device_pwm *pwm_dev;      /* PWM�豸��� */
struct rt_device_pwm *pwm2_dev;      /* PWM2�豸��� */
int pwm_Initiation(void)
{
    rt_err_t rt_err = RT_EOK;
    rt_uint16_t pulse = 0;  /* ��ʼʹ��Ϊ�� */

    /* ����UV���豸 */
    pwm_dev = (struct rt_device_pwm *)rt_device_find(PWM_DEV_NAME);
    if (pwm_dev == RT_NULL)
    {
        rt_kprintf("pwm sample run failed! can't find %s device!\n", PWM_DEV_NAME);
        rt_err = RT_NULL;
    }
    else {
        rt_kprintf("rt_sensor find %s device init success!\n", PWM_DEV_NAME);
    }
    /* ����ˮ���豸 */
    pwm2_dev = (struct rt_device_pwm *)rt_device_find(PWM2_DEV_NAME);
    if (pwm2_dev == RT_NULL)
    {
        rt_kprintf("pwm sample run failed! can't find %s device!\n", PWM2_DEV_NAME);
        rt_err = RT_NULL;
    }
    else {
        rt_kprintf("rt_sensor find %s device init success!\n", PWM2_DEV_NAME);
    }
    /* ����PWM���ں�������Ĭ��ֵ */
    rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, pulse);
    rt_pwm_set(pwm2_dev, PWM_DEV_CHANNEL, period, pulse);
    /* ʹ���豸 */
    rt_pwm_enable(pwm_dev, PWM_DEV_CHANNEL);
    rt_pwm_enable(pwm2_dev, PWM_DEV_CHANNEL);
    return rt_err;
}
/*a,b��Χ��0~10*/
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
        rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, 0);//UV��
        rt_pwm_set(pwm2_dev, PWM_DEV_CHANNEL, period, 0);//ˮ��
    } else {
        rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, period*0.1*a);//UV��
        rt_pwm_set(pwm2_dev, PWM_DEV_CHANNEL, period, period*0.7+period*0.03*b);//ˮ��
    }
}
INIT_APP_EXPORT(pwm_Initiation);
