#include "main.h"
#include <stdio.h>
#include <stdint.h>

void delay(volatile uint32_t count)
{

	for(volatile uint32_t i = 0;i<count;i++){

	}

}

int main(void)
{

	RCC_AHB1ENR_t volatile *const pClkCtrlReg     =     (RCC_AHB1ENR_t*)   ADDR_AHB1ENR_REG;
	GPIOx_MODE_t  volatile *const pPortDModeReg   =     (GPIOx_MODE_t*)    ADDR_GPIOD_MODE;
	GPIOx_ODR_t   volatile *const pPortDoutReg    =     (GPIOx_ODR_t*)     ADDR_GPIOD_ODR;
	GPIOx_MODE_t  volatile *const pPortAModeReg   =     (GPIOx_MODE_t*)    ADDR_GPIOA_MODE;
	GPIOx_IDR_t   volatile *const pPortAinReg     =     (GPIOx_IDR_t*)     ADDR_GPIOA_IDR;


	pClkCtrlReg ->gpiod_en = CLOCK_ENABLE;
	pClkCtrlReg ->gpioa_en = CLOCK_ENABLE;

	pPortDModeReg ->pin_12 = MODE_CONF_OUTPUT;
	pPortDModeReg ->pin_13 = MODE_CONF_OUTPUT;
	pPortDModeReg ->pin_14 = MODE_CONF_OUTPUT;
	pPortDModeReg ->pin_15 = MODE_CONF_OUTPUT;
	pPortAModeReg -> pin_0 = MODE_CONF_INPUT;

	uint8_t current_mode = 0;


	while(1)
	{

		if(pPortAinReg->pin_0 == PIN_STATE_HIGH)
		{
			delay(150000);

			current_mode++;
			if(current_mode > 2){
				current_mode = 0;
			}

			while(pPortAinReg ->pin_0 == PIN_STATE_HIGH){
				delay(150000);
			}
		}

				switch(current_mode){
				case 0:
					pPortDoutReg ->pin_12 = PIN_STATE_HIGH;
					pPortDoutReg ->pin_13 = PIN_STATE_HIGH;
			    	pPortDoutReg ->pin_14 = PIN_STATE_HIGH;
			    	pPortDoutReg ->pin_15 = PIN_STATE_HIGH;
			    	break;

				case 1:
					pPortDoutReg->pin_12 = PIN_STATE_HIGH;
					delay(DELAY_COUNT);
					pPortDoutReg->pin_12 = PIN_STATE_LOW;

					pPortDoutReg->pin_13 = PIN_STATE_HIGH;
					delay(DELAY_COUNT);
					pPortDoutReg->pin_13 = PIN_STATE_LOW;

					pPortDoutReg->pin_14 = PIN_STATE_HIGH;
					delay(DELAY_COUNT);
					pPortDoutReg->pin_14 = PIN_STATE_LOW;

					pPortDoutReg->pin_15 = PIN_STATE_HIGH;
					delay(DELAY_COUNT);
					pPortDoutReg->pin_15 = PIN_STATE_LOW;

					break;

				case 2:
					pPortDoutReg->pin_12 = PIN_STATE_HIGH;
					pPortDoutReg->pin_13 = PIN_STATE_HIGH;
					pPortDoutReg->pin_14 = PIN_STATE_HIGH;
					pPortDoutReg->pin_15 = PIN_STATE_HIGH;
					delay(DELAY_COUNT);

					pPortDoutReg->pin_12 = PIN_STATE_LOW;
					pPortDoutReg->pin_13 = PIN_STATE_LOW;
					pPortDoutReg->pin_14 = PIN_STATE_LOW;
					pPortDoutReg->pin_15 = PIN_STATE_LOW;
					delay(DELAY_COUNT);
					break;
				}
		}










	return 0;
}
