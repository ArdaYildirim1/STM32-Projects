#include "stm32f407xx.h"
#include "stm32f407xx_spi_driver.h"
#include <stdint.h>


/*********************************************************************
 * @fn      		  - SPI_PeriClockControl
 *
 * @brief             - This function enables or disables peripheral clock for the given SPI port
 *
 * @param[in]         - Base address of the SPI peripheral
 * @param[in]         - ENABLE or DISABLE macros
 * @param[in]         -
 *
 * @return            - none
 *
 * @Note              - none
 *
 */
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{



		if(EnorDi == ENABLE)
			{
				if(pSPIx == SPI1)
				{
					SPI1_PCLK_EN();
				}
				else if (pSPIx == SPI2)
				{
					SPI2_PCLK_EN();
				}
				else if (pSPIx == SPI3)
				{
					SPI3_PCLK_EN();
				}
			}
			else
			{

				if(pSPIx == SPI1)
				{
					SPI1_PCLK_DI();
				}
				else if (pSPIx == SPI2)
				{
					SPI2_PCLK_DI();
				}
				else if (pSPIx == SPI3)
				{
					SPI3_PCLK_DI();
				}
			}

}

void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
		{
			pSPIx->SPI_CR1 |=  (1 << SPI_CR1_SSI);
		}else
		{
			pSPIx->SPI_CR1 &= ~(1 << SPI_CR1_SSI);
		}
}


/*********************************************************************
 * @fn      		  - SPI_SSOEConfig
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            - none
 *
 * @Note              - none
 *
 */

void SPI_SSOEConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{

	if(EnorDi == ENABLE)
			{
				pSPIx->SPI_CR2 |=  (1 << SPI_CR2_SSOE);
			}else
			{
				pSPIx->SPI_CR2 &= ~(1 << SPI_CR2_SSOE);
			}

}


/*********************************************************************
 * @fn      		  - SPI_Init
 *
 * @brief             - This function initializes the SPI peripheral
 *
 * @param[in]         - Pointer to the SPI Handle structure
 * @param[in]         -
 * @param[in]         -
 *
 * @return            - none
 *
 * @Note              - none
 *
 */
void SPI_Init(SPI_Handle_t *pSPIHandle)
{

	SPI_PeriClockControl(pSPIHandle->pSPIx, ENABLE);

	uint32_t tempReg =0;

	tempReg |= pSPIHandle->SPIConfig.SPI_DeviceMode << SPI_CR1_MSTR;

	if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD)
	{

		tempReg &= ~(1 << SPI_CR1_BIDIMODE);

	}else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD)
	{
		tempReg |= (1 << SPI_CR1_BIDIMODE);

	}else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY)
	{

		tempReg &= ~(1 << SPI_CR1_BIDIMODE);
		tempReg |= (1 << SPI_CR1_RXONLY);

	}else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_TXONLY)
	{

		tempReg &= ~(1 << SPI_CR1_BIDIMODE);

	}

	tempReg |= pSPIHandle->SPIConfig.SPI_SclkSpeed << SPI_CR1_BR;
	tempReg |= pSPIHandle->SPIConfig.SPI_DFF<< SPI_CR1_DFF;
	tempReg |= pSPIHandle->SPIConfig.SPI_CPOL << SPI_CR1_CPOL;
	tempReg |= pSPIHandle->SPIConfig.SPI_CPHA << SPI_CR1_CPHA;
	tempReg |= pSPIHandle->SPIConfig.SPI_SSM << SPI_CR1_SSM;

	pSPIHandle->pSPIx->SPI_CR1 = tempReg;
}


/*********************************************************************
 * @fn      		  - SPI_DeInit
 *
 * @brief             - This function de-initializes the SPI peripheral (Resets the registers)
 *
 * @param[in]         - Base address of the SPI peripheral
 * @param[in]         -
 * @param[in]         -
 *
 * @return            - none
 *
 * @Note              - none
 *
 */
void SPI_DeInit(SPI_RegDef_t *pSPIx)
{

	if(pSPIx == SPI1)
			{
				SPI1_REG_RESET();
			}
			else if(pSPIx == SPI2)
			{
				SPI2_REG_RESET();
			}
			else if(pSPIx == SPI3)
			{
				SPI3_REG_RESET();
			}

}


uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName)
{
	if(pSPIx->SPI_SR & FlagName)
	{
		return FLAG_SET;
	}
	return FLAG_RESET;
}

void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		pSPIx->SPI_CR1 |= (1 << SPI_CR1_SPE);
	}else
	{
		pSPIx->SPI_CR1 &= ~(1 << SPI_CR1_SPE);
	}
}

/*********************************************************************
 * @fn      		  - SPI_SendData
 *
 * @brief             - This function sends data over the SPI peripheral
 *
 * @param[in]         - Base address of the SPI peripheral
 * @param[in]         - Pointer to the transmit buffer (TxBuffer)
 * @param[in]         - Number of bytes to be transmitted (Length)
 *
 * @return            - none
 *
 * @Note              - This is a blocking call (Polling based)
 *
 */
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len)
{

	while(Len > 0)
	{
		while(SPI_GetFlagStatus(pSPIx, SPI_TXE_FLAG) == FLAG_RESET);

		if(pSPIx->SPI_CR1 & (1 << SPI_CR1_DFF))
		{
			///16-bit
			pSPIx->SPI_DR = *((uint16_t*)pTxBuffer);

			Len -=2;

			pTxBuffer +=2;
		}
		else
		{
			pSPIx->SPI_DR = *pTxBuffer;
			Len--;
			pTxBuffer++;
		}


	}


}


/*********************************************************************
 * @fn      		  - SPI_ReceiveData
 *
 * @brief             - This function receives data over the SPI peripheral
 *
 * @param[in]         - Base address of the SPI peripheral
 * @param[in]         - Pointer to the receive buffer (RxBuffer)
 * @param[in]         - Number of bytes to be received (Length)
 *
 * @return            - none
 *
 * @Note              - none
 *
 */
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len)
{

	while(Len > 0)
		{
			while(SPI_GetFlagStatus(pSPIx, SPI_RXNE_FLAG) == FLAG_RESET);

			if(pSPIx->SPI_CR1 & (1 << SPI_CR1_DFF))
			{
				//16-bit
				*((uint16_t*)pRxBuffer) = pSPIx->SPI_DR;;

				Len -=2;

				pRxBuffer +=2;
			}
			else
			{	// 8-bit
				*pRxBuffer = pSPIx->SPI_DR ;
				Len--;
				pRxBuffer++;
			}


		}

}


/*********************************************************************
 * @fn      		  - SPI_IRQInterruptConfig
 *
 * @brief             - This function enables or disables the SPI interrupt in the NVIC
 *
 * @param[in]         - IRQ number of the SPI peripheral
 * @param[in]         - ENABLE or DISABLE macros
 * @param[in]         -
 *
 * @return            - none
 *
 * @Note              - none
 *
 */
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{


}


/*********************************************************************
 * @fn      		  - SPI_IRQPriorityConfig
 *
 * @brief             - This function configures the interrupt priority for the SPI peripheral
 *
 * @param[in]         - IRQ number of the SPI peripheral
 * @param[in]         - Priority value to be set
 * @param[in]         -
 *
 * @return            - none
 *
 * @Note              - none
 *
 */
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority)
{

}


/*********************************************************************
 * @fn      		  - SPI_IRQHandling
 *
 * @brief             - This function handles the SPI interrupt request
 *
 * @param[in]         - Pointer to the SPI Handle structure
 * @param[in]         -
 * @param[in]         -
 *
 * @return            - none
 *
 * @Note              - none
 *
 */
void SPI_IRQHandling(SPI_Handle_t *pHandle)
{

}












