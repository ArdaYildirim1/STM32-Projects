# STM32 Projects

A collection of embedded systems projects developed on the **STM32F4DISCOVERY** board, documenting my progression from HAL-based development to bare-metal, register-level programming and custom peripheral driver development.

## Repository Structure

### `/BareMetal-Projects`
Projects and peripheral drivers implemented through direct register manipulation, without any hardware abstraction library. All register definitions are written from scratch based on the STM32F407 Reference Manual (RM0090), demonstrating a working understanding of the microcontroller's memory-mapped peripherals.

### `/HAL-Projects`
Projects built using the STM32 HAL library, covering core peripheral usage such as GPIO, timers, PWM, ADC, and interrupt handling.

## Bare-Metal Driver Status

| Driver | Features | Status |
|---|---|---|
| GPIO | Input/output, alternate functions, EXTI interrupts, NVIC configuration | ✅ Done |
| SPI | Blocking and interrupt-based TX/RX, IRQ handling, OVR error handling, application callbacks | ✅ Done |
| I2C | — | ⏳ In progress |
| USART | — | 🔜 Planned |

## Example Applications

- **SPI command handling**
  STM32 (master) sends commands to an Arduino Uno (slave), validates the ACK/NACK response, and controls an LED on the Arduino side.

- **SPI interrupt-based message reception**
  The Arduino signals data availability through a GPIO interrupt (falling edge on PD6). The STM32 then reads the message byte by byte over SPI using interrupt-driven APIs and prints it via SWV ITM.

**Hardware setup:** STM32F4DISCOVERY + Arduino Uno, connected through a 3.3V ↔ 5V bidirectional logic level shifter.

## Lessons Learned

- **Enable peripheral clocks first.**
  EXTI interrupts on PD6 never fired because the SYSCFG clock was not enabled. Writes to `SYSCFG_EXTICR` were silently ignored, so the EXTI line stayed mapped to port A instead of port D.

- **Write-1-to-act registers need a direct write.**
  NVIC `ISER`/`ICER` registers should be written with `=`, not `|=`. A read-modify-write on `ICER` can unintentionally disable every other interrupt that is currently enabled in the same register.

- **SPI is a data swap.**
  Every byte the master sends clocks in a byte from the slave. Dummy reads are needed to clear `RXNE` after sending, and dummy writes are needed to receive data from the slave.

- **Interrupt-driven code must stop its own interrupts.**
  The `TXE` flag remains set while the transmit buffer is empty, so `TXEIE` must be disabled once transmission completes; otherwise the CPU gets stuck re-entering the ISR.

## Tools & Environment

- **Microcontroller:** STM32F407VG (STM32F4DISCOVERY)
- **Language:** C
- **IDE:** STM32CubeIDE
- **Debugging:** ST-LINK, SWV ITM console, logic analyzer
- **Reference:** STM32F407 Reference Manual (RM0090), STM32F407 Datasheet

## Goal

Building a strong foundation in embedded systems by understanding both the practical (HAL) and fundamental (register-level) sides of microcontroller programming. Having started writing custom peripheral drivers, my next goals are completing the I2C and USART drivers and moving toward real-time, hardware-focused applications.

## Contact

Open to discussing embedded systems, feedback, or collaboration. Feel free to reach out via the email on my GitHub profile.
