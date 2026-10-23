#include <string.h>
#include <stdint.h>
#include "stm32f407xx.h"

// Arduino commands
#define COMMAND_LED_CTRL      0x50
#define COMMAND_SENSOR_READ   0x51
#define COMMAND_LED_READ      0x52
#define COMMAND_PRINT         0x53
#define COMMAND_ID_READ       0x54

#define LED_ON     1
#define LED_OFF    0

// Arduino analog pins
#define ANALOG_PIN0   0
#define ANALOG_PIN1   1
#define ANALOG_PIN2   2
#define ANALOG_PIN3   3
#define ANALOG_PIN4   4

// Arduino LED pin
#define LED_PIN    9


void delay(void)
{
	for(uint32_t i = 0 ;i<500000/2; i++);
}



/*
 * PB15 --> SPI2_MOSI
 * PB14 --> SPI2_MISO
 * PB13 --> SPI2_SCLK
 * PB12 --> SPI2_NSS
 * Alternate function: AF5
 */


void SPI2_GPIOInits(void)
{

    GPIO_Handle_t SPIPins;

    GPIO_PeriClockControl(GPIOB, ENABLE);

    SPIPins.pGPIOx = GPIOB;
    SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
    SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
    SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

    // SCLK
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
    GPIO_Init(&SPIPins);

    // MOSI
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
    GPIO_Init(&SPIPins);

    // MISO
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
    GPIO_Init(&SPIPins);

    // NSS
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
    GPIO_Init(&SPIPins);
}


void SPI2_Inits(void)
{
    SPI_Handle_t SPI2handle;

    SPI2handle.pSPIx = SPI2;
    SPI2handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
    SPI2handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
    SPI2handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV8;   // 2 MHz
    SPI2handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
    SPI2handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
    SPI2handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
    SPI2handle.SPIConfig.SPI_SSM = SPI_SSM_DI;

    SPI_Init(&SPI2handle);
}


void GPIO_ButtonInit(void)
{
    GPIO_Handle_t GPIOBtn;

    GPIO_PeriClockControl(GPIOA, ENABLE);

    GPIOBtn.pGPIOx = GPIOA;
    GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
    GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_INPUT;
    GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    GPIOBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

    GPIO_Init(&GPIOBtn);
}

uint8_t SPI_VerifyResponse(uint8_t ackbyte)
{
    if(ackbyte == 0xF5)
    {
        return 1;
    }
    return 0;
}

int main(void)
{

	 GPIO_ButtonInit();
	 SPI2_GPIOInits();
	 SPI2_Inits();

	 SPI_SSOEConfig(SPI2, ENABLE);

	 uint8_t dummy_write = 0xFF;
	 uint8_t dummy_read;


	    while(1)
	    {

	        while( ! GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0) );
	        delay();   // debounce


	        SPI_PeripheralControl(SPI2, ENABLE);

	        uint8_t commandcode = COMMAND_LED_CTRL;
	        uint8_t ackbyte;


	        SPI_SendData(SPI2, &commandcode, 1);
	        SPI_ReceiveData(SPI2, &dummy_read, 1);

	        delay();

	        SPI_SendData(SPI2, &dummy_write, 1);
	        SPI_ReceiveData(SPI2, &ackbyte, 1);


	        if( SPI_VerifyResponse(ackbyte) )
	        {
	            uint8_t pin = LED_PIN;
	            uint8_t value = LED_ON;

	            SPI_SendData(SPI2, &pin, 1);
	            SPI_ReceiveData(SPI2, &dummy_read, 1);

	            SPI_SendData(SPI2, &value, 1);
	            SPI_ReceiveData(SPI2, &dummy_read, 1);
	        }


	        while( SPI_GetFlagStatus(SPI2, SPI_BUSY_FLAG) );


	        SPI_PeripheralControl(SPI2, DISABLE);
	    }





	return 0;
}

