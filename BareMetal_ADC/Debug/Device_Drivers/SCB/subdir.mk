################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Device_Drivers/SCB/scb.c \
../Device_Drivers/SCB/uart.c \
../Device_Drivers/SCB/i2c.c

OBJS += \
./Device_Drivers/SCB/scb.o \
./Device_Drivers/SCB/uart.o \
./Device_Drivers/SCB/i2c.o

# Each subdirectory must supply rules for building sources it contributes
Device_Drivers/SCB/%.o: ../Device_Drivers/SCB/%.c
	@echo 'Building file: $^'
	@echo 'Invoking: ARM-GCC C Compiler'
	$(CC) $(CFLAGS) -c -o $@ $^ 
	@echo 'Finished building: $^'