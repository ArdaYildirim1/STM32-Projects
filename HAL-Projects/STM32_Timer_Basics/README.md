# STM32 Timer-Based LED Control

A non-blocking LED blink implementation on the STM32F4DISCOVERY board using a hardware timer with interrupt-driven periodic execution.

## Overview

This project demonstrates how to configure and use a general-purpose timer (TIM3) to trigger a periodic interrupt without relying on the CPU or blocking delay functions. The timer runs independently in the background, toggling an LED at a precise, calculated interval.

## Hardware

- STM32F4DISCOVERY (STM32F407VGT6)
- On-board LED (LD5)

## Implementation Details

- **Timer:** TIM3, configured with an internal clock source
- **Prescaler / Auto-Reload:** Calculated to generate a 1 Hz interrupt from an 84 MHz timer clock
- **Execution model:** Interrupt-driven (`HAL_TIM_Base_Start_IT`), leaving the main loop completely free
- **Callback:** `HAL_TIM_PeriodElapsedCallback()` toggles the LED state on every timer overflow

## Key Concepts Demonstrated

- Timer clock derivation from the APB bus and system clock tree
- Prescaler and Auto-Reload Register (ARR) calculation for a target frequency
- Interrupt-based (non-blocking) timing, as opposed to `HAL_Delay()`
- NVIC configuration for timer interrupts

## Frequency Calculation

Timer Clock ÷ (Prescaler + 1) ÷ (ARR + 1) = Target Frequency (Hz)
84,000,000 ÷ 8400 ÷ 10,000 = 1 Hz

## Why Interrupt-Driven Timing Matters

Unlike `HAL_Delay()`, which blocks the CPU for the entire delay duration, a hardware timer interrupt allows the main loop to remain free for other tasks while the timing logic runs entirely in hardware. This is a foundational pattern for real-time embedded systems.
