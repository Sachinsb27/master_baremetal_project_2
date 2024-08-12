################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Device_Drivers/TRNG/trng.c

OBJS += \
./Device_Drivers/TRNG/trng.o

# Each subdirectory must supply rules for building sources it contributes
Device_Drivers/TRNG/%.o: ../Device_Drivers/TRNG/%.c
	@echo 'Building file: $^'
	@echo 'Invoking: ARM-GCC C Compiler'
	$(CC) $(CFLAGS) -c -o $@ $^ 
	@echo 'Finished building: $^'

