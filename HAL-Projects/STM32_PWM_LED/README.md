# STM32 PWM LED Control

PWM (Pulse Width Modulation) signal generation on the STM32F4DISCOVERY board, used to control LED brightness through variable duty cycle.

## Hardware Used
- STM32F4DISCOVERY (STM32F407VGT6)
- On-board LED (specify which LED you used, e.g. LD4)

## What This Project Covers
- **PWM fundamentals:** understanding duty cycle, frequency, and how a timer generates a PWM waveform
- **Timer PWM mode configuration:** setting up a timer channel in PWM output mode via CubeMX
- **Application 1:** basic PWM output driving an LED at a fixed duty cycle
- **Application 2:** variable duty cycle, creating a "breathing" LED effect (brightness fading in and out)

## What I Learned
- How duty cycle determines average voltage/brightness perceived by the human eye
- Configuring a timer channel (`TIM_CHANNEL_x`) for PWM generation using `HAL_TIM_PWM_Start()`
- Adjusting duty cycle at runtime using `__HAL_TIM_SET_COMPARE()`
- The relationship between PWM frequency, timer clock, prescaler, and ARR (building on timer knowledge from the previous project)

## Duty Cycle Calculation

Duty Cycle (%) = (CCR / ARR) × 100

Where CCR (Capture/Compare Register) sets the "on" time within each PWM period.
