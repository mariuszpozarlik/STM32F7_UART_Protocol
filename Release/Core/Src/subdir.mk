################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/commands.c \
../Core/Src/gpio.c \
../Core/Src/main.c \
../Core/Src/protocol.c \
../Core/Src/ringbuff.c \
../Core/Src/stm32f7xx_hal_msp.c \
../Core/Src/stm32f7xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f7xx.c \
../Core/Src/usart.c \
../Core/Src/usb_otg.c 

OBJS += \
./Core/Src/commands.o \
./Core/Src/gpio.o \
./Core/Src/main.o \
./Core/Src/protocol.o \
./Core/Src/ringbuff.o \
./Core/Src/stm32f7xx_hal_msp.o \
./Core/Src/stm32f7xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f7xx.o \
./Core/Src/usart.o \
./Core/Src/usb_otg.o 

C_DEPS += \
./Core/Src/commands.d \
./Core/Src/gpio.d \
./Core/Src/main.d \
./Core/Src/protocol.d \
./Core/Src/ringbuff.d \
./Core/Src/stm32f7xx_hal_msp.d \
./Core/Src/stm32f7xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f7xx.d \
./Core/Src/usart.d \
./Core/Src/usb_otg.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/commands.o: ../Core/Src/commands.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/STM32F7xx_HAL_Driver/Inc -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/CMSIS/Device/ST/STM32F7xx/Include -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/CMSIS/Include -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/commands.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/gpio.o: ../Core/Src/gpio.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/STM32F7xx_HAL_Driver/Inc -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/CMSIS/Device/ST/STM32F7xx/Include -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/CMSIS/Include -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/gpio.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/main.o: ../Core/Src/main.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/STM32F7xx_HAL_Driver/Inc -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/CMSIS/Device/ST/STM32F7xx/Include -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/CMSIS/Include -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/main.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/protocol.o: ../Core/Src/protocol.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/STM32F7xx_HAL_Driver/Inc -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/CMSIS/Device/ST/STM32F7xx/Include -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/CMSIS/Include -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/protocol.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/ringbuff.o: ../Core/Src/ringbuff.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/STM32F7xx_HAL_Driver/Inc -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/CMSIS/Device/ST/STM32F7xx/Include -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/CMSIS/Include -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/ringbuff.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/stm32f7xx_hal_msp.o: ../Core/Src/stm32f7xx_hal_msp.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/STM32F7xx_HAL_Driver/Inc -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/CMSIS/Device/ST/STM32F7xx/Include -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/CMSIS/Include -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/stm32f7xx_hal_msp.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/stm32f7xx_it.o: ../Core/Src/stm32f7xx_it.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/STM32F7xx_HAL_Driver/Inc -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/CMSIS/Device/ST/STM32F7xx/Include -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/CMSIS/Include -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/stm32f7xx_it.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/syscalls.o: ../Core/Src/syscalls.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/STM32F7xx_HAL_Driver/Inc -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/CMSIS/Device/ST/STM32F7xx/Include -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/CMSIS/Include -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/syscalls.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/sysmem.o: ../Core/Src/sysmem.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/STM32F7xx_HAL_Driver/Inc -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/CMSIS/Device/ST/STM32F7xx/Include -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/CMSIS/Include -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/sysmem.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/system_stm32f7xx.o: ../Core/Src/system_stm32f7xx.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/STM32F7xx_HAL_Driver/Inc -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/CMSIS/Device/ST/STM32F7xx/Include -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/CMSIS/Include -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/system_stm32f7xx.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/usart.o: ../Core/Src/usart.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/STM32F7xx_HAL_Driver/Inc -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/CMSIS/Device/ST/STM32F7xx/Include -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/CMSIS/Include -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/usart.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/usb_otg.o: ../Core/Src/usb_otg.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/STM32F7xx_HAL_Driver/Inc -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/CMSIS/Device/ST/STM32F7xx/Include -IC:/Users/Mariusz/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.2/Drivers/CMSIS/Include -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/usb_otg.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

