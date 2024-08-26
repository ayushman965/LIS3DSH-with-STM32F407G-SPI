################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/User_Defined/LIS3DH_Lib/LIS3DH_Lib.c 

OBJS += \
./Drivers/User_Defined/LIS3DH_Lib/LIS3DH_Lib.o 

C_DEPS += \
./Drivers/User_Defined/LIS3DH_Lib/LIS3DH_Lib.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/User_Defined/LIS3DH_Lib/%.o Drivers/User_Defined/LIS3DH_Lib/%.su Drivers/User_Defined/LIS3DH_Lib/%.cyclo: ../Drivers/User_Defined/LIS3DH_Lib/%.c Drivers/User_Defined/LIS3DH_Lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/THRSL/CubeIDE_Workspace/STM32F407G_Accelerometer/Drivers/User_Defined/LIS3DH_Lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-User_Defined-2f-LIS3DH_Lib

clean-Drivers-2f-User_Defined-2f-LIS3DH_Lib:
	-$(RM) ./Drivers/User_Defined/LIS3DH_Lib/LIS3DH_Lib.cyclo ./Drivers/User_Defined/LIS3DH_Lib/LIS3DH_Lib.d ./Drivers/User_Defined/LIS3DH_Lib/LIS3DH_Lib.o ./Drivers/User_Defined/LIS3DH_Lib/LIS3DH_Lib.su

.PHONY: clean-Drivers-2f-User_Defined-2f-LIS3DH_Lib

