################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libraries/HAL_Drivers/drv_adc.c \
../libraries/HAL_Drivers/drv_common.c \
../libraries/HAL_Drivers/drv_gpio.c \
../libraries/HAL_Drivers/drv_pwm.c \
../libraries/HAL_Drivers/drv_soft_i2c.c \
../libraries/HAL_Drivers/drv_usart_v2.c 

OBJS += \
./libraries/HAL_Drivers/drv_adc.o \
./libraries/HAL_Drivers/drv_common.o \
./libraries/HAL_Drivers/drv_gpio.o \
./libraries/HAL_Drivers/drv_pwm.o \
./libraries/HAL_Drivers/drv_soft_i2c.o \
./libraries/HAL_Drivers/drv_usart_v2.o 

C_DEPS += \
./libraries/HAL_Drivers/drv_adc.d \
./libraries/HAL_Drivers/drv_common.d \
./libraries/HAL_Drivers/drv_gpio.d \
./libraries/HAL_Drivers/drv_pwm.d \
./libraries/HAL_Drivers/drv_soft_i2c.d \
./libraries/HAL_Drivers/drv_usart_v2.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/HAL_Drivers/%.o: ../libraries/HAL_Drivers/%.c
	arm-none-eabi-gcc -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\board\ports" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\board" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\libraries\HAL_Drivers\config" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\libraries\HAL_Drivers" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\packages\bmp180-latest" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\packages\dhtxx-latest\inc" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\packages\ssd1306-latest\inc" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\ra\arm\CMSIS_5\CMSIS\Core\Include" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\ra\fsp\inc\api" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\ra\fsp\inc\instances" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\ra\fsp\inc" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\ra_cfg\fsp_cfg\bsp" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\ra_cfg\fsp_cfg" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\ra_gen" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\rt-thread\components\drivers\include" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\rt-thread\components\drivers\sensors" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\rt-thread\components\finsh" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\rt-thread\components\libc\compilers\common" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\rt-thread\components\libc\compilers\newlib" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\rt-thread\components\libc\posix\io\poll" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\rt-thread\components\libc\posix\io\stdio" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\rt-thread\components\libc\posix\ipc" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\rt-thread\include" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\rt-thread\libcpu\arm\common" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\rt-thread\libcpu\arm\cortex-m4" -include"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\rtconfig_preinc.h" -std=gnu11 -mcpu=cortex-m33 -mthumb -mfpu=fpv5-sp-d16 -mfloat-abi=hard -ffunction-sections -fdata-sections -Dgcc -O0 -gdwarf-2 -g -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

