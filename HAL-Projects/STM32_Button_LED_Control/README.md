# STM32 Button LED Control

Button-based LED control on the STM32F4DISCOVERY board, progressing from a simple press/release check to a sequential "running light" pattern with adjustable speed.

## Hardware Used
- STM32F4DISCOVERY (STM32F407VGT6)
- On-board user button (B1)
- On-board LEDs: LD3 (orange), LD4 (green), LD5 (red), LD6 (blue)

## What This Project Covers
- **Basic button read:** turning an LED on while the button is held (`HAL_GPIO_ReadPin`)
- **Press/release handling:** turning the LED off when the button is released (if/else logic)
- **Sequential LED pattern ("Kara Şimşek"):** all four LEDs light up and turn off in sequence, then reverse, creating a running-light effect
- **Adjustable speed:** each time the button is pressed, the delay between LED steps decreases, making the pattern run faster, with a lower bound to prevent the delay from going negative

## What I Learned
- Reading digital input with `HAL_GPIO_ReadPin()`
- Implementing press-and-hold behavior with if/else logic
- Building a sequential LED pattern using multiple `HAL_GPIO_WritePin()` calls and `HAL_Delay()`
- Dynamically adjusting a delay variable based on button interaction
- Preventing variable underflow by bounding a value (`Delay > 0` check) before it's passed to a HAL function
