################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/bin/initdb/initdb.c 

OBJS += \
./src/bin/initdb/initdb.o 

C_DEPS += \
./src/bin/initdb/initdb.d 


# Each subdirectory must supply rules for building sources it contributes
src/bin/initdb/%.o: ../src/bin/initdb/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM gcc compiler'
	arm-xilinx-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


