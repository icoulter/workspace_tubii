################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/backend/utils/error/assert.c \
../src/backend/utils/error/elog.c 

OBJS += \
./src/backend/utils/error/assert.o \
./src/backend/utils/error/elog.o 

C_DEPS += \
./src/backend/utils/error/assert.d \
./src/backend/utils/error/elog.d 


# Each subdirectory must supply rules for building sources it contributes
src/backend/utils/error/%.o: ../src/backend/utils/error/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM gcc compiler'
	arm-xilinx-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


