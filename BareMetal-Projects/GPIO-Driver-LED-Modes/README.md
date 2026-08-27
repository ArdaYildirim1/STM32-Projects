# GPIO Driver — Bare-Metal LED Mode Control

A bare-metal GPIO driver for STM32F4DISCOVERY, implemented entirely through direct register manipulation — no HAL library used. The project demonstrates peripheral clock control, GPIO configuration, and pin I/O using custom bit-field structures mapped directly onto hardware registers.

## Hardware Used
- STM32F4DISCOVERY (STM32F407VGT6)
- On-board LEDs (PD12–PD15)
- On-board user button (PA0)

## What This Project Does

The application cycles through three LED display modes, controlled via button press:

- **Mode 0:** All four LEDs on (steady)
- **Mode 1:** LEDs light up sequentially, one at a time
- **Mode 2:** All four LEDs blink together

Pressing the button advances to the next mode, with button debouncing handled through a wait-for-release loop.

## Technical Approach

Instead of using HAL functions like `HAL_GPIO_WritePin()`, this project defines the relevant peripheral registers (RCC_AHB1ENR, GPIOx_MODER, GPIOx_ODR, GPIOx_IDR) as C structs with bit-fields, mapped directly to their memory addresses via the STM32F407 Reference Manual (RM0090).

```c
typedef struct {
    uint32_t pin_0  : 2;
    uint32_t pin_1  : 2;
    // ...
} GPIOx_MODE_t;

#define GPIOD_MODE  ((GPIOx_MODE_t*)0x40020C00UL)
```

This approach makes register access more readable (`pPortDModeReg->pin_12 = MODE_CONF_OUTPUT`) while still operating at the same level as raw register manipulation.

## What I Learned

- How peripheral clocks must be explicitly enabled via RCC before a peripheral becomes responsive
- Reading and interpreting register definitions from the STM32F407 Reference Manual (RM0090)
- Mapping register bit-fields to C struct members for readable, type-safe register access
- The relationship between HAL abstractions and the underlying