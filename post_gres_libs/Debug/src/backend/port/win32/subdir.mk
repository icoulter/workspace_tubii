################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/backend/port/win32/mingwcompat.c \
../src/backend/port/win32/security.c \
../src/backend/port/win32/signal.c \
../src/backend/port/win32/socket.c \
../src/backend/port/win32/timer.c 

OBJS += \
./src/backend/port/win32/mingwcompat.o \
./src/backend/port/win32/security.o \
./src/backend/port/win32/signal.o \
./src/backend/port/win32/socket.o \
./src/backend/port/win32/timer.o 

C_DEPS += \
./src/backend/port/win32/mingwcompat.d \
./src/backend/port/win32/security.d \
./src/backend/port/win32/signal.d \
./src/backend/port/win32/socket.d \
./src/backend/port/win32/timer.d 


# Each subdirectory must supply rules for building sources it contributes
src/backend/port/win32/%.o: ../src/backend/port/win32/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM gcc compiler'
	arm-xilinx-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


