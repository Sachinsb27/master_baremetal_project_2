################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application_Source/main.c \
../Application_Source/user_cfg.c 

OBJS += \
./Application_Source/main.o \
./Application_Source/user_cfg.o 

# Each subdirectory must supply rules for building sources it contributes
Application_Source/%.o: ../Application_Source/%.c
	@echo 'Building file: $^'
	@echo 'Invoking: ARM-GCC C Compiler'
	$(CC) $(CFLAGS) -c -o $@ $^  
	@echo 'Finished building: $^'

