# STM32 Projects

A collection of embedded systems projects developed on the STM32F4DISCOVERY board, documenting my progression from HAL-based development to bare-metal register-level programming.

## Repository Structure

### `/BareMetal-Projects`
Projects implemented through direct register manipulation, without any hardware abstraction library. These demonstrate a working understanding of the microcontroller's memory-mapped peripherals, built from register definitions in the STM32F407 Reference Manual (RM0090).

### `/HAL-Projects`
Projects built using the STM32 HAL library, covering core peripheral usage such as GPIO, timers, PWM, ADC, and interrupt handling.

## Tools & Environment

- **Microcontroller:** STM32F407VG (STM32F4DISCOVERY)
- **Language:** C
- **IDE:** STM32CubeIDE
- **Reference:** STM32F407 Reference Manual (RM0090)

## Goal

Building a strong foundation in embedded systems by understanding both the practical (HAL) and fundamental (register-level) sides of microcontroller programming — with the long-term goal of developing custom peripheral drivers and working on real-time, hardware-focused applications.

## Contact

Open to discussing embedded systems, feedback, or collaboration.
