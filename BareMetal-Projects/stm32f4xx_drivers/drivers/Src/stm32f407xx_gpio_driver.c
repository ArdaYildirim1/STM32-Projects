#include "stm32f407xx_gpio_driver.h"

/*
 * Peripheral Clock Setup
 */

/********************************************************
 * @fn              - GPIO_PeriClockControl
 * @brief           - This function enables or disables peripheral clock for the given GPIO port.
 *
 * @param[in]       - base address of the gpio peripheral
 * @param[in]       - ENABLE or DISABLE macros
 *
 * @return          - none
 * @Note            - none
 ********************************************************/
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_EN();
		}
		else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_EN();
		}
		else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_EN();
		}
		else if(pGPIOx == GPIOD)
		{
			GPIOD_PCLK_EN();
		}
		else if(pGPIOx == GPIOE)
		{
			GPIOE_PCLK_EN();
		}
		else if(pGPIOx == GPIOF)
		{
			GPIOF_PCLK_EN();
		}
		else if(pGPIOx == GPIOG)
		{
			GPIOG_PCLK_EN();
		}
		else if(pGPIOx == GPIOH)
		{
			GPIOH_PCLK_EN();
		}
		else if(pGPIOx == GPIOI)
		{
			GPIOI_PCLK_EN();
		}
	}
	else
	{

		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_DI();
		}
		else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_DI();
		}
		else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_DI();
		}
		else if(pGPIOx == GPIOD)
		{
			GPIOD_PCLK_DI();
		}
		else if(pGPIOx == GPIOE)
		{
			GPIOE_PCLK_DI();
		}
		else if(pGPIOx == GPIOF)
		{
			GPIOF_PCLK_DI();
		}
		else if(pGPIOx == GPIOG)
		{
			GPIOG_PCLK_DI();
		}
		else if(pGPIOx == GPIOH)
		{
			GPIOH_PCLK_DI();
		}
		else if(pGPIOx == GPIOI)
		{
			GPIOI_PCLK_DI();
		}
	}
}

/*
 * Init and De-init
 */

/********************************************************
 * @fn              - GPIO_Init
 * @brief           - This function initializes the GPIO port and pin according to the specified parameters in the handle.
 *
 * @param[in]       - pointer to GPIO_Handle_t structure that contains the configuration information
 *
 * @return          - none
 * @Note            - none
 ********************************************************/
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
	uint32_t temp = 0;
	//1. configure the mode of the gpio pin

	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG){

		temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
		pGPIOHandle->pGPIOx->MODER &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber ));
		pGPIOHandle->pGPIOx->MODER |= temp;


	}else
	{

		if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
		{

			//1. configure the FTSR
			EXTI->FTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			//clear the corresponding RTSR bit
			EXTI->RTSR &= ~( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);




		}else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
		{

			//1. configure the RTSR
			EXTI->RTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			//clear the corresponding FTSR bit
			EXTI->FTSR &= ~( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);


		}else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FRT)
		{

			//1. configure the FTSR and RTSR
			EXTI->RTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->FTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}

		//2. Configure the GPIO port selection in SYSCFG_EXTICR
		uint8_t temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4;
		uint8_t temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4;
		uint8_t portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);
		uint8_t exti_bit_pos = temp2 *4;
		SYSCFG->EXTICR[temp1] &= ~(0xF << exti_bit_pos);
		SYSCFG->EXTICR[temp1] |=  (portcode << exti_bit_pos);


		//3.enable the exti interrupt delivery using IMR
		EXTI->IMR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);


	}
	temp = 0;

	//2. configure the speed

	temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OSPEEDR  &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OSPEEDR |= temp;
	temp = 0;


	//3. configure the pupd settings

		temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle->pGPIOx->PUPDR |= temp;
		temp = 0;


	//4. configure the optype

		temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << ( pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 << ( pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber ));
		pGPIOHandle->pGPIOx->OTYPER |= temp;
		temp = 0;

	//5. configure the alt functionality

		if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
		{

			uint8_t temp1, temp2;

			//(AFR[0] veya AFR[1])?
			temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;

			//(AFR[0] veya AFR[1])?
			temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8;

			pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0xF << (4* temp2));

			pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4 * temp2));

			temp1 = 0;
			temp2 = 0;


		}





}

/********************************************************
 * @fn              - GPIO_DeInit
 * @brief           - This function de-initializes the GPIO port registers to their default reset values.
 *
 * @param[in]       - base address of the gpio peripheral
 *
 * @return          - none
 * @Note            - none
 ********************************************************/
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{

	if(pGPIOx == GPIOA)
		{
			GPIOA_REG_RESET();
		}
		else if(pGPIOx == GPIOB)
		{
			GPIOB_REG_RESET();
		}
		else if(pGPIOx == GPIOC)
		{
			GPIOC_REG_RESET();
		}
		else if(pGPIOx == GPIOD)
		{
			GPIOD_REG_RESET();
		}
		else if(pGPIOx == GPIOE)
		{
			GPIOE_REG_RESET();
		}
		else if(pGPIOx == GPIOF)
		{
			GPIOF_REG_RESET();
		}
		else if(pGPIOx == GPIOG)
		{
			GPIOG_REG_RESET();
		}
		else if(pGPIOx == GPIOH)
		{
			GPIOH_REG_RESET();
		}
		else if(pGPIOx == GPIOI)
		{
			GPIOI_REG_RESET();
		}
	}


/*
 * Data read and write
 */

/********************************************************
 * @fn              - GPIO_ReadFromInputPin
 * @brief           - Reads the logic value from a specific GPIO input pin.
 *
 * @param[in]       - base address of the gpio peripheral
 * @param[in]       - GPIO pin number to read from
 *
 * @return          - 0 or 1 (pin state)
 * @Note            - none
 ********************************************************/
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
    uint8_t value;

    value = (uint8_t)(pGPIOx->IDR >>PinNumber ) & (0x00000001);

    return value;
}

/********************************************************
 * @fn              - GPIO_ReadFromInputPort
 * @brief           - Reads the logic values of the entire GPIO input port.
 *
 * @param[in]       - base address of the gpio peripheral
 *
 * @return          - 16-bit value containing the state of all 16 pins of the port
 * @Note            - none
 ********************************************************/
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
	uint16_t value;

	value = (uint16_t)pGPIOx->IDR;

	return value;
}

/********************************************************
 * @fn              - GPIO_WriteToOutputPin
 * @brief           - Writes a logic value (0 or 1) to a specific GPIO output pin.
 *
 * @param[in]       - base address of the gpio peripheral
 * @param[in]       - GPIO pin number to write to
 * @param[in]       - Value to be written (ENABLE/DISABLE veya SET/RESET)
 *
 * @return          - none
 * @Note            - none
 ********************************************************/
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value)
{

	if(Value == GPIO_PIN_SET)
	{
		//write 1
		pGPIOx->ODR |= (1 << PinNumber);

	}else
	{
		// write 0
		pGPIOx->ODR &= ~( 1 << PinNumber);
	}

}

/********************************************************
 * @fn              - GPIO_WriteToOutputPort
 * @brief           - Writes a 16-bit value to the entire GPIO output port.
 *
 * @param[in]       - base address of the gpio peripheral
 * @param[in]       - 16-bit value to be written to the port
 *
 * @return          - none
 * @Note            - none
 ********************************************************/
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value)
{

	pGPIOx->ODR = Value;


}

/********************************************************
 * @fn              - GPIO_ToggleOutputPin
 * @brief           - Toggles (inverts) the state of a specific GPIO output pin.
 *
 * @param[in]       - base address of the gpio peripheral
 * @param[in]       - GPIO pin number to toggle
 *
 * @return          - none
 * @Note            - none
 ********************************************************/
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{


	pGPIOx->ODR ^= (1 << PinNumber);


}


/*
 * IRQ Configuration and ISR handling
 */

/********************************************************
 * @fn              - GPIO_IRQInterruptConfig
 * @brief           - Configures the IRQ number, priority and enables/disables the interrupt.
 *
 * @param[in]       - IRQ number of the interrupt
 * @param[in]       - ENABLE or DISABLE macro
 *
 * @return          - none
 * @Note            - none
 ********************************************************/
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{

	if(EnorDi == ENABLE)
	{
		if(IRQNumber <=31)
		{

			//program ISER0 register
			*NVIC_ISER0 |= (1 << IRQNumber);

		}else if(IRQNumber > 31 && IRQNumber <64) // 32 to 63
		{

			//program ISER1 register
			*NVIC_ISER1 |= (1 << IRQNumber % 32);

		}else if(IRQNumber >= 64 && IRQNumber <96) // 64 to 95
		{

			//program ISER2 register
			*NVIC_ISER2 |= (1 << IRQNumber % 64);

		}


	}else
	{
		if(IRQNumber <=31)
				{

					//program ICER0 register
					*NVIC_ICER0 |= (1 << IRQNumber);

				}else if(IRQNumber > 31 && IRQNumber <64) // 32 to 63
				{

					//program ICER1 register
					*NVIC_ICER1 |= (1 << IRQNumber % 32);

				}else if(IRQNumber >= 64 && IRQNumber <96) // 64 to 95
				{

					//program ICER2 register
					*NVIC_ICER2 |= (1 << IRQNumber % 64);

				}
	}





}

/********************************************************
 * @fn              - GPIO_IRQPriorityConfig
 * @brief           - Configures the priority.
 *
 * @param[in]       - Priority of the IRQ
 *
 * @return          - none
 * @Note            - none
 ********************************************************/
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority)
{

	//1. first lets find out the ipr register
	uint8_t iprx 			= 	IRQNumber / 4;
	uint8_t iprx_section 	= 	IRQNumber % 4;

	uint8_t shift_amount = (8* iprx_section) + (8- NO_PR_BITS_IMPLEMENTED);
	*(NVIC_PR_BASEADDR + (iprx*4)) |= (IRQPriority << (shift_amount));


}


/********************************************************
 * @fn              - GPIO_IRQHandling
 *
 * @brief           - Clears the interrupt pending bit for the given pin when an interrupt occurs.
 *
 * @param[in]       - GPIO pin number from which the interrupt triggered
 *
 * @return          - none
 * @Note            - none
 ********************************************************/
void GPIO_IRQHandling(uint8_t PinNumber)
{

	if(EXTI->PR & (1 << PinNumber))
	{
		EXTI->PR  |= (1 << PinNumber);
	}


}
