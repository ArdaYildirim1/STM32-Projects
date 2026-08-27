# STM32 Servo Motor Control

This project demonstrates how to control a standard servo motor by generating hardware-based PWM (Pulse Width Modulation) signals using an STM32F407VG Discovery development board.

## Hardware & Configuration
* **Microcontroller:** STM32F407VGT6
* **Peripheral:** TIM2 (Timer 2)
* **Channel:** Channel 2 (Pin PA1)
* **Motor:** Standard 180° Servo (e.g., SG90 / MG996R)

## PWM Signal Mathematics
Servo motors typically require a 50 Hz (20 ms) PWM signal. Based on the APB1 timer clock (84 MHz), the following configuration is applied:
* **Prescaler (PSC):** 1680 - 1
* **Auto-Reload Register (ARR):** 1000 - 1

With this setup, the timer counts 50,000 times per second. Since the period (ARR) is 1000, the signal frequency is `1000 / 50,000 = 0.02 seconds (20 ms)`.

### Duty Cycle and Angle Mapping
The HIGH (Logic 1) duration of the signal (Pulse) is determined by the Timer's Capture/Compare Register (CCR) value:
* **5% Duty Cycle (1.0 ms):** CCR = 50 &rarr; Moves the motor to the minimum hardware limit (e.g., -90° or 0°).
* **7.5% Duty Cycle (1.5 ms):** CCR = 75 &rarr; Aligns the motor to the center position (e.g., 0° or 90°).
* **10% Duty Cycle (2.0 ms):** CCR = 100 &rarr; Moves the motor to the maximum hardware limit (e.g., +90° or 180°).

## Operation Scenario
Upon initialization, the microcontroller sequentially commands the servo to move to its minimum limit, center position, and maximum limit. A 1-second (1000 ms) delay is applied between each movement to allow the physical actuator to reach the target coordinate. This sequence repeats continuously in an infinite loop.
