################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/backend/utils/hash/dynahash.c \
../src/backend/utils/hash/hashfn.c \
../src/backend/utils/hash/pg_crc.c 

OBJS += \
./src/backend/utils/hash/dynahash.o \
./src/backend/utils/hash/hashfn.o \
./src/backend/utils/hash/pg_crc.o 

C_DEPS += \
./src/backend/utils/hash/dynahash.d \
./src/backend/utils/hash/hashfn.d \
./src/backend/utils/hash/pg_crc.d 


# Each subdirectory must supply rules for building sources it contributes
src/backend/utils/hash/%.o: ../src/backend/utils/hash/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM gcc compiler'
	arm-xilinx-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


