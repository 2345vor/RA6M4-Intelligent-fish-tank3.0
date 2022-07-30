/*
 * �����嵥������һ�������豸���ղ��������ݵ�ʾ������
 * ���̵����� uart_dma_sample ��������ն�
 * ������ø�ʽ��uart_dma_sample uart2
 * ������ͣ�����ڶ���������Ҫʹ�õĴ����豸���ƣ�Ϊ����ʹ��Ĭ�ϵĴ����豸
 * �����ܣ�ͨ������ uart2 ����ַ���"hello RT-Thread!"����ͨ������ uart2 ����һ���ַ���������������ͨ�����ݽ�����ʹ�ÿ���̨��ʾ��Ч���ݡ�
*/

//5A 00 00 00 01 01 00 0B 00 00 A5         ����
//5A 00 00 00 01 00 00 0B 00 00 A5         �ص�

#include"uart.h"
#define LED3_PIN    BSP_IO_PORT_01_PIN_06
#define buzzer_PIN  BSP_IO_PORT_04_PIN_03//����������
#define SAMPLE_UART_NAME                 "uart0"
#define DATA_CMD_END                     '\r'       /* ����λ����Ϊ \r�����س��� */
#define ONE_DATA_MAXLEN                  12         /* ���������ݵ���󳤶� */



/* ���ڽ�����Ϣ���ź��� */
static struct rt_semaphore rx_sem;
static rt_device_t serial;

/* �������ݻص����� */
static rt_err_t uart_rx_ind(rt_device_t dev, rt_size_t size)
{
    /* ���ڽ��յ����ݺ�����жϣ����ô˻ص�������Ȼ���ͽ����ź��� */
    if (size > 0)
    {
        rt_sem_release(&rx_sem);
    }
    return RT_EOK;
}

static char uart_sample_get_char(void)
{
    char ch;

    while (rt_device_read(serial, 0, &ch, 1) == 0)
    {
        rt_sem_control(&rx_sem, RT_IPC_CMD_RESET, RT_NULL);
        rt_sem_take(&rx_sem, RT_WAITING_FOREVER);
    }
    return ch;
}
/* ���ݽ����߳� */
static void control_thread_entry(void)
{
    char ch;
    char  data[ONE_DATA_MAXLEN];
    static char i = 0;
    unsigned char *adc_value, *bmp_value;
    while (1)
    {
        ch = uart_sample_get_char();
        if(ch == DATA_CMD_END)
        {
            data[i++] = '\0';
            rt_kprintf("data= 0x");//CMD uart7��ӡ uart0����16������
            for (int var = 0; var < ONE_DATA_MAXLEN-1; ++var) {
                rt_kprintf("%x",data[var]);
            }
            rt_kprintf("\r\n");
            rt_thread_mdelay(1);
            if (data[0]==0x5a&&data[10]==0xa5) {//У��ͷ����β��
                if (data[4]==0x00) {//��������
                    rt_kprintf("Keep on \r\n");
                   }
                else if (data[4]==0x01) {//�޸�����//����LED����
                    rt_kprintf("Action \r\n");
                    rt_pin_write(LED3_PIN, data[5]);//�����������෴
                    pwm_action(data[2],data[3]);//�ƺ�ˮ��
                    rt_pin_write(buzzer_PIN, data[1]);//�����������෴
                }
                else if (data[4]==0x02) {
                    rt_kprintf("Automatic \r\n");
                    adc_value = adc_read();
                    bmp_value = bmp_read();
                    data[2] = 10*adc_value[0]/35*(330-adc_value[1])/330;//ˮ��
                    data[3] = 10*adc_value[0]/30*(101-bmp_value[0])/5;//ˮ��
                    pwm_action(data[2],data[3]);//�ƺ�ˮ��
                }
            }
            else {//У��ʶ�𣬷������ݲ��Ϸ�
                rt_kprintf("data input Illegal ! please input :5A 00 00 00 01 01 00 0B 00 00 A5 \r\n",data);
            }
            rt_device_write(serial, 0, &data, sizeof(data));//uart0��ӡ����ָ��
            for (int var = 0; var < sizeof(data); ++var) {
                data[var] = 0x00;
            }//��������
            i = 0;//���»�ȡ
            continue;
        }
        i = (i >= ONE_DATA_MAXLEN-1) ? ONE_DATA_MAXLEN-1 : i;
        data[i++] = ch;

    }
}

/*uart0��������߳�*/
void serial_thread_entry(rt_uint8_t a,rt_uint8_t b)
{
    unsigned char *adc_value, gpio_value[2], *bmp_value, *dht_value, pwm_value[2];
    char str1[45];
    char HeadByte[45] ="/*KAANSATQRO";
    adc_value = adc_read();
    gpio_value[0] = rt_pin_read(buzzer_PIN),gpio_value[1] = rt_pin_read(LED3_PIN);
    bmp_value = bmp_read();
    dht_value = cat_dhtxx();
    pwm_value[0] = a,pwm_value[1] = b;
    rt_sprintf(str1, "%s,%d,%d", HeadByte, adc_value[0],adc_value[1]);
    rt_sprintf(str1, "%s,%d,%d", str1,gpio_value[0],gpio_value[1]);
    rt_sprintf(str1, "%s,%d,%d", str1,bmp_value[0],bmp_value[1]);
    rt_sprintf(str1, "%s,%d,%d", str1,dht_value[0],dht_value[1]);
    rt_sprintf(str1, "%s,%d,%d", str1,pwm_value[0],pwm_value[1]);
    rt_sprintf(str1, "%s%s", str1,"*/ \r\n");
    rt_device_write(serial, 0, str1, sizeof(str1) );
    rt_thread_mdelay(500);
}

static int uart_data_sample(int argc, char *argv[])
{
    rt_err_t ret = RT_EOK;
    char uart_name[RT_NAME_MAX];
    char str[] = "hello RT-Thread!\r\n";

    if (argc == 2)
    {
        rt_strncpy(uart_name, argv[1], RT_NAME_MAX);
    }
    else
    {
        rt_strncpy(uart_name, SAMPLE_UART_NAME, RT_NAME_MAX);
    }

    /* ����ϵͳ�еĴ����豸 */
    serial = rt_device_find(uart_name);
    if (!serial)
    {
        rt_kprintf("find %s failed!\n", uart_name);
        return RT_ERROR;
    }

    /* ��ʼ���ź��� */
    rt_sem_init(&rx_sem, "rx_sem", 0, RT_IPC_FLAG_FIFO);
    /* ���жϽ��ռ���ѯ����ģʽ�򿪴����豸 */
    rt_device_open(serial, RT_DEVICE_FLAG_INT_RX);
    /* ���ý��ջص����� */
    rt_device_set_rx_indicate(serial, uart_rx_ind);
    /* �����ַ��� */
    rt_device_write(serial, 0, str, (sizeof(str) - 1));
    /* ���� control_thread �߳� */
//    rt_thread_t control_thread = rt_thread_create("control", (void (*)(void *parameter))control_thread_entry, RT_NULL, 1024, 30, 10);
    rt_thread_t control_thread = rt_thread_create("control", (void (*)(void *parameter))control_thread_entry, RT_NULL, 1024, 25, 10);

    /* �����ɹ��������߳� */
    if (control_thread != RT_NULL)
    {
        rt_thread_startup(control_thread);
    }
    else
    {
        ret = RT_ERROR;
    }

    return ret;
}

/* ������ msh �����б��� */
//MSH_CMD_EXPORT(uart_data_sample, uart device sample);
INIT_APP_EXPORT(uart_data_sample);

