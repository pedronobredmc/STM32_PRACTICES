################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/gpio.c \
../Src/interrupt.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/systic.c 

OBJS += \
./Src/gpio.o \
./Src/interrupt.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/systic.o 

C_DEPS += \
./Src/gpio.d \
./Src/interrupt.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/systic.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DSTM32F103xB=STM32F103xB -c -I"C:/Users/pedro/Documents/Micro/Pratica06_Adc_Pwm/Inc" -I"C:/Users/pedro/Documents/Micro/Pratica06_Adc_Pwm/F1_Header/Device/ST/STM32F1xx/Include" -I"C:/Users/pedro/Documents/Micro/Pratica06_Adc_Pwm/F1_Header/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/gpio.cyclo ./Src/gpio.d ./Src/gpio.o ./Src/gpio.su ./Src/interrupt.cyclo ./Src/interrupt.d ./Src/interrupt.o ./Src/interrupt.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/systic.cyclo ./Src/systic.d ./Src/systic.o ./Src/systic.su

.PHONY: clean-Src

