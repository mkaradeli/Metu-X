################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../app/Drivers/Motor/Motor.cpp 

OBJS += \
./app/Drivers/Motor/Motor.o 

CPP_DEPS += \
./app/Drivers/Motor/Motor.d 


# Each subdirectory must supply rules for building sources it contributes
app/Drivers/Motor/%.o app/Drivers/Motor/%.su app/Drivers/Motor/%.cyclo: ../app/Drivers/Motor/%.cpp app/Drivers/Motor/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H730xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/alica/OneDrive/Documents/GitHub/Metu-X/embed-fw/metux-ahr/app/include" -I"C:/Users/alica/OneDrive/Documents/GitHub/Metu-X/embed-fw/metux-ahr/app/Drivers/Lidar" -I"C:/Users/alica/OneDrive/Documents/GitHub/Metu-X/embed-fw/metux-ahr/app/Drivers/Motor" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-app-2f-Drivers-2f-Motor

clean-app-2f-Drivers-2f-Motor:
	-$(RM) ./app/Drivers/Motor/Motor.cyclo ./app/Drivers/Motor/Motor.d ./app/Drivers/Motor/Motor.o ./app/Drivers/Motor/Motor.su

.PHONY: clean-app-2f-Drivers-2f-Motor

