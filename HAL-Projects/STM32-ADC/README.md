# STM32 ADC Sensors

Analog-to-digital conversion on STM32F4DISCOVERY, reading sensor values via polling method.

## Hardware Used
- STM32F4DISCOVERY (STM32F407VGT6)
- ADC1 Channel 15 (PC5) — potentiometer input

## What This Project Covers
- ADC initialization and channel configuration via CubeMX
- Polling-based conversion (`HAL_ADC_PollForConversion`)
- 12-bit resolution analog reading

## What I Learned
- ADC channel-to-pin mapping and GPIO Analog mode configuration
- Polling vs interrupt-driven ADC reading
- Debugging pin configuration issues using STM32CubeMX pinout view

## Note
Code compiles successfully and follows correct HAL configuration patterns. Hardware verification pending — will be tested and confirmed once physical board access is available.
