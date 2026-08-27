# 🚀 STM32 Projects Portfolio

Welcome to my STM32 projects repository! This workspace is dedicated to my journey in embedded systems and microcontrollers. Here, you will find a structured collection of my work, ranging from low-level hardware interactions to higher-level hardware abstraction layer implementations.

Most of the projects here are developed and tested on the **STM32F4DISCOVERY** board.

## 📂 Repository Structure

### 🛠️ 1. BareMetal_Projects
This section contains projects where I interact directly with the microcontroller's registers. It showcases a deep understanding of the hardware architecture without relying on external abstraction libraries.

* **[embedded-c-learning](./BareMetal_Projects/embedded-c-learning):** My personal journey and fundamental exercises in learning Embedded C and bare-metal STM32 programming.
* **[stm32-baremetal-gpio-driver](./BareMetal_Projects/stm32-baremetal-gpio-driver):** Custom GPIO driver implementation built from scratch at the register level.

### 🧩 2. HAL_Projects
This section includes projects developed using the STM32 Hardware Abstraction Layer (HAL) library. It focuses on rapid prototyping, clean code architecture, and utilizing ST's official drivers.

* **[STM32-ADC](./HAL_Projects/STM32-ADC):** Analog-to-digital conversion reading sensor values via the polling method.
* **[STM32_Button_LED_Control](./HAL_Projects/STM32_Button_LED_Control):** Handling GPIO button inputs and controlling LEDs accordingly using HAL library.
* **[STM32_External_Interrupt](./HAL_Projects/STM32_External_Interrupt):** Handling external hardware interrupts.
* **[STM32_LED_Blinky](./HAL_Projects/STM32_LED_Blinky):** The classic "Hello World" of embedded systems, blinking an LED using HAL GPIO functions.
* **[STM32_PWM_LED](./HAL_Projects/STM32_PWM_LED):** PWM signal generation for LED brightness and motor speed control.
* **[STM32_Servo_Control](./HAL_Projects/STM32_Servo_Control):** Hardware PWM generation and dynamic servo motor control using Timer 2.
* **[STM32_Timer_Basics](./HAL_Projects/STM32_Timer_Basics):** Interrupt-driven, timer-based LED control.

## ⚙️ Tools & Environment
* **Microcontroller:** STM32F407VG (STM32F4 Discovery Board)
* **Language:** C
* **IDE:** STM32CubeIDE

## 🤝 Let's Connect
Feel free to explore the code, open issues if you spot any bugs, or reach out if you want to chat about embedded systems!
