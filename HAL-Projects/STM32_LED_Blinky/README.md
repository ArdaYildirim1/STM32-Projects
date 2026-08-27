# STM32 LED Blinky

A simple GPIO application on the STM32F4DISCOVERY board that turns an LED on and makes it blink using the HAL library.

## Hardware Used
- STM32F4DISCOVERY (STM32F407VGT6)
- On-board LD4 (green LED)

## What I Learned
- Using HAL_GPIO_WritePin() to set a GPIO pin state
- Using HAL_GPIO_TogglePin() to toggle a pin state
- Using HAL_Delay() for timing control
- Creating and configuring a project with STM32CubeIDE and STM32CubeMX
