################################################################################
# �Զ����ɵ��ļ�����Ҫ�༭��
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/adc.c \
../src/hal_entry.c \
../src/pwmled.c \
../src/uart.c 

OBJS += \
./src/adc.o \
./src/hal_entry.o \
./src/pwmled.o \
./src/uart.o 

C_DEPS += \
./src/adc.d \
./src/hal_entry.d \
./src/pwmled.d \
./src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	arm-none-eabi-gcc -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\board\ports" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\board" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\libraries\HAL_Drivers\config" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\libraries\HAL_Drivers" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\packages\bmp180-latest" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\packages\dhtxx-latest\inc" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\packages\ssd1306-latest\inc" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\ra\arm\CMSIS_5\CMSIS\Core\Include" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\ra\fsp\inc\api" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\ra\fsp\inc\instances" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\ra\fsp\inc" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\ra_cfg\fsp_cfg\bsp" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\ra_cfg\fsp_cfg" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\ra_gen" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\rt-thread\components\drivers\include" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\rt-thread\components\drivers\sensors" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\rt-thread\components\finsh" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\rt-thread\components\libc\compilers\common" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\rt-thread\components\libc\compilers\newlib" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\rt-thread\components\libc\posix\io\poll" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\rt-thread\components\libc\posix\io\stdio" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\rt-thread\components\libc\posix\ipc" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\rt-thread\include" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\rt-thread\libcpu\arm\common" -I"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\rt-thread\libcpu\arm\cortex-m4" -include"D:\RT-ThreadStudio\workspace\RA6M4-Intelligent-fish-tank2.0\rtconfig_preinc.h" -std=gnu11 -mcpu=cortex-m33 -mthumb -mfpu=fpv5-sp-d16 -mfloat-abi=hard -ffunction-sections -fdata-sections -Dgcc -O0 -gdwarf-2 -g -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

