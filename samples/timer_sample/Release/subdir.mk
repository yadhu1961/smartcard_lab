################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../communication.c \
../timer.c \
../timer_sample.c \
../uart_debug.c 

OBJS += \
./communication.o \
./timer.o \
./timer_sample.o \
./uart_debug.o 

C_DEPS += \
./communication.d \
./timer.d \
./timer_sample.d \
./uart_debug.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644 -DF_CPU=4831168UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


