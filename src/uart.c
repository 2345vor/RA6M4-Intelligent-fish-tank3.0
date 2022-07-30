/*
 * 程序清单：这是一个串口设备接收不定长数据的示例代码
 * 例程导出了 uart_dma_sample 命令到控制终端
 * 命令调用格式：uart_dma_sample uart2
 * 命令解释：命令第二个参数是要使用的串口设备名称，为空则使用默认的串口设备
 * 程序功能：通过串口 uart2 输出字符串"hello RT-Thread!"，并通过串口 uart2 输入一串字符（不定长），再通过数据解析后，使用控制台显示有效数据。
*/

//5A 00 00 00 01 01 00 0B 00 00 A5         开灯
//5A 00 00 00 01 00 00 0B 00 00 A5         关灯

#include"uart.h"
#define LED3_PIN    BSP_IO_PORT_01_PIN_06
#define buzzer_PIN  BSP_IO_PORT_04_PIN_03//蜂鸣器定义
#define SAMPLE_UART_NAME                 "uart0"
#define DATA_CMD_END                     '\r'       /* 结束位设置为 \r，即回车符 */
#define ONE_DATA_MAXLEN                  12         /* 不定长数据的最大长度 */



/* 用于接收消息的信号量 */
static struct rt_semaphore rx_sem;
static rt_device_t serial;

/* 接收数据回调函数 */
static rt_err_t uart_rx_ind(rt_device_t dev, rt_size_t size)
{
    /* 串口接收到数据后产生中断，调用此回调函数，然后发送接收信号量 */
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
/* 数据解析线程 */
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
            rt_kprintf("data= 0x");//CMD uart7打印 uart0接收16进制数
            for (int var = 0; var < ONE_DATA_MAXLEN-1; ++var) {
                rt_kprintf("%x",data[var]);
            }
            rt_kprintf("\r\n");
            rt_thread_mdelay(1);
            if (data[0]==0x5a&&data[10]==0xa5) {//校验头部和尾部
                if (data[4]==0x00) {//保持命令
                    rt_kprintf("Keep on \r\n");
                   }
                else if (data[4]==0x01) {//修改命令//操作LED灯亮
                    rt_kprintf("Action \r\n");
                    rt_pin_write(LED3_PIN, data[5]);//蜂鸣器操作相反
                    pwm_action(data[2],data[3]);//灯和水泵
                    rt_pin_write(buzzer_PIN, data[1]);//蜂鸣器操作相反
                }
                else if (data[4]==0x02) {
                    rt_kprintf("Automatic \r\n");
                    adc_value = adc_read();
                    bmp_value = bmp_read();
                    data[2] = 10*adc_value[0]/35*(330-adc_value[1])/330;//水泵
                    data[3] = 10*adc_value[0]/30*(101-bmp_value[0])/5;//水泵
                    pwm_action(data[2],data[3]);//灯和水泵
                }
            }
            else {//校验识别，返回数据不合法
                rt_kprintf("data input Illegal ! please input :5A 00 00 00 01 01 00 0B 00 00 A5 \r\n",data);
            }
            rt_device_write(serial, 0, &data, sizeof(data));//uart0打印接收指令
            for (int var = 0; var < sizeof(data); ++var) {
                data[var] = 0x00;
            }//数组清零
            i = 0;//重新获取
            continue;
        }
        i = (i >= ONE_DATA_MAXLEN-1) ? ONE_DATA_MAXLEN-1 : i;
        data[i++] = ch;

    }
}

/*uart0串口输出线程*/
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

    /* 查找系统中的串口设备 */
    serial = rt_device_find(uart_name);
    if (!serial)
    {
        rt_kprintf("find %s failed!\n", uart_name);
        return RT_ERROR;
    }

    /* 初始化信号量 */
    rt_sem_init(&rx_sem, "rx_sem", 0, RT_IPC_FLAG_FIFO);
    /* 以中断接收及轮询发送模式打开串口设备 */
    rt_device_open(serial, RT_DEVICE_FLAG_INT_RX);
    /* 设置接收回调函数 */
    rt_device_set_rx_indicate(serial, uart_rx_ind);
    /* 发送字符串 */
    rt_device_write(serial, 0, str, (sizeof(str) - 1));
    /* 创建 control_thread 线程 */
//    rt_thread_t control_thread = rt_thread_create("control", (void (*)(void *parameter))control_thread_entry, RT_NULL, 1024, 30, 10);
    rt_thread_t control_thread = rt_thread_create("control", (void (*)(void *parameter))control_thread_entry, RT_NULL, 1024, 25, 10);

    /* 创建成功则启动线程 */
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

/* 导出到 msh 命令列表中 */
//MSH_CMD_EXPORT(uart_data_sample, uart device sample);
INIT_APP_EXPORT(uart_data_sample);

