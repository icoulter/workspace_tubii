################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/backend/utils/mb/conversion_procs/utf8_and_euc_jp/utf8_and_euc_jp.c 

OBJS += \
./src/backend/utils/mb/conversion_procs/utf8_and_euc_jp/utf8_and_euc_jp.o 

C_DEPS += \
./src/backend/utils/mb/conversion_procs/utf8_and_euc_jp/utf8_and_euc_jp.d 


# Each subdirectory must supply rules for building sources it contributes
src/backend/utils/mb/conversion_procs/utf8_and_euc_jp/%.o: ../src/backend/utils/mb/conversion_procs/utf8_and_euc_jp/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM gcc compiler'
	arm-xilinx-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


