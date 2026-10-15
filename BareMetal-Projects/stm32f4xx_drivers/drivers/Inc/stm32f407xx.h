#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_

#include <stdint.h>

#define  __vo volatile
#define FLASH_BASEADDR        0x08000000U
#define SRAM1_BASEADDR        0x20000000U
#define SRAM2_BASEADDR        0x2001C000U  /* SRAM1 + 112KB */
#define ROM_BASEADDR          0x1FFF0000U  /* System Memory */
#define OTP_BASEADDR          0x1FFF7800U  /* OTP Area */

#define SRAM_BASEADDR         SRAM1_BASEADDR /* SRAM1 is used as Main RAM */



/* Main base address of all peripherals (Peripheral Base Address) */
#define PERIPH_BASE           0x40000000U

/* APB1 Peripherals Base Address (Starts from the bottom, i.e., PERIPH_BASE) */
#define APB1PERIPH_BASE       PERIPH_BASE

/* Base addresses of other buses according to the address map in the Reference Manual */
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x00010000U)  /* e.g., 0x40010000 */
#define AHB1PERIPH_BASE       (PERIPH_BASE + 0x00020000U)  /* e.g., 0x40020000 */
#define AHB2PERIPH_BASE       0x50000000U                  /* e.g., USB OTG, Camera, etc. */

/* Peripherals connected to the AHB1 Bus */
#define GPIOA_BASEADDR        (AHB1PERIPH_BASE + 0x0000U)
#define GPIOB_BASEADDR        (AHB1PERIPH_BASE + 0x0400U)
#define GPIOC_BASEADDR        (AHB1PERIPH_BASE + 0x0800U)
#define GPIOD_BASEADDR        (AHB1PERIPH_BASE + 0x0C00U)
#define GPIOE_BASEADDR        (AHB1PERIPH_BASE + 0x1000U)
#define GPIOF_BASEADDR        (AHB1PERIPH_BASE + 0x1400U)
#define GPIOG_BASEADDR        (AHB1PERIPH_BASE + 0x1800U)
#define GPIOH_BASEADDR        (AHB1PERIPH_BASE + 0x1C00U)
#define GPIOI_BASEADDR        (AHB1PERIPH_BASE + 0x2000U)
#define RCC_BASEADDR          (AHB1PERIPH_BASE + 0x3800U)


/* Peripherals connected to the APB1 Bus */
#define I2C1_BASEADDR         (APB1PERIPH_BASE + 0x5400U)
#define I2C2_BASEADDR         (APB1PERIPH_BASE + 0x5800U)
#define I2C3_BASEADDR         (APB1PERIPH_BASE + 0x5C00U)
#define SPI2_BASEADDR         (APB1PERIPH_BASE + 0x3800U)
#define SPI3_BASEADDR         (APB1PERIPH_BASE + 0x3C00U)
#define USART2_BASEADDR       (APB1PERIPH_BASE + 0x4400U)
#define USART3_BASEADDR       (APB1PERIPH_BASE + 0x4800U)
#define UART4_BASEADDR        (APB1PERIPH_BASE + 0x4C00U)
#define UART5_BASEADDR        (APB1PERIPH_BASE + 0x5000U)

/* Peripherals connected to the APB2 Bus */
#define SPI1_BASEADDR         (APB2PERIPH_BASE + 0x3000U)
#define USART1_BASEADDR       (APB2PERIPH_BASE + 0x1000U)
#define USART6_BASEADDR       (APB2PERIPH_BASE + 0x1400U)
#define EXTI_BASEADDR         (APB2PERIPH_BASE + 0x3C00U)
#define SYSCFG_BASEADDR       (APB2PERIPH_BASE + 0x3800U)








typedef struct
{
	__vo uint32_t MODER;   /* GPIO port mode register address 		offset: 0x00 */
	__vo uint32_t OTYPER;  /* GPIO port output type register */
	__vo uint32_t OSPEEDR; /* GPIO port output speed register */
	__vo uint32_t PUPDR;   /* GPIO port pull-up/pull-down register */
	__vo uint32_t IDR;     /* GPIO port input data register */
	__vo uint32_t ODR;     /* GPIO port output data register */
	__vo uint32_t BSRR;    /* GPIO port bit set/reset register */
	__vo uint32_t LCKR;    /* GPIO port configuration lock register */
	__vo uint32_t AFR[2];  /* GPIO alternate function registers */
}GPIO_RegDef_t;


typedef struct
{
    __vo uint32_t CR;            /* 0x00: RCC clock control register */
    __vo uint32_t PLLCFGR;       /* 0x04: RCC PLL configuration register */
    __vo uint32_t CFGR;          /* 0x08: RCC clock configuration register */
    __vo uint32_t CIR;           /* 0x0C: RCC clock interrupt register */
    __vo uint32_t AHB1RSTR;      /* 0x10: RCC AHB1 peripheral reset register */
    __vo uint32_t AHB2RSTR;      /* 0x14: RCC AHB2 peripheral reset register */
    __vo uint32_t AHB3RSTR;      /* 0x18: RCC AHB3 peripheral reset register */
    __vo uint32_t Reserved0;     /* 0x1C: Reserved */
    __vo uint32_t APB1RSTR;      /* 0x20: RCC APB1 peripheral reset register */
    __vo uint32_t APB2RSTR;      /* 0x24: RCC APB2 peripheral reset register */
    __vo uint32_t Reserved1[2];  /* 0x28 - 0x2C: Reserved */
    __vo uint32_t AHB1ENR;       /* 0x30: RCC AHB1 peripheral clock enable register */
    __vo uint32_t AHB2ENR;       /* 0x34: RCC AHB2 peripheral clock enable register */
    __vo uint32_t AHB3ENR;       /* 0x38: RCC AHB3 peripheral clock enable register */
    __vo uint32_t Reserved2;     /* 0x3C: Reserved */
    __vo uint32_t APB1ENR;       /* 0x40: RCC APB1 peripheral clock enable register */
    __vo uint32_t APB2ENR;       /* 0x44: RCC APB2 peripheral clock enable register */
    __vo uint32_t Reserved3[2];  /* 0x48 - 0x4C: Reserved */
    __vo uint32_t AHB1LPENR;     /* 0x50: RCC AHB1 peripheral clock enable in low power mode register */
    __vo uint32_t AHB2LPENR;     /* 0x54: RCC AHB2 peripheral clock enable in low power mode register */
    __vo uint32_t AHB3LPENR;     /* 0x58: RCC AHB3 peripheral clock enable in low power mode register */
    __vo uint32_t Reserved4;     /* 0x5C: Reserved */
    __vo uint32_t APB1LPENR;     /* 0x60: RCC APB1 peripheral clock enable in low power mode register */
    __vo uint32_t APB2LPENR;     /* 0x64: RCC APB2 peripheral clock enable in low power mode register */
    __vo uint32_t Reserved5[2];  /* 0x68 - 0x6C: Reserved */
    __vo uint32_t BDCR;          /* 0x70: RCC Backup domain control register */
    __vo uint32_t CSR;           /* 0x74: RCC clock control & status register */
    __vo uint32_t Reserved6[2];  /* 0x78 - 0x7C: Reserved */
    __vo uint32_t SSCGR;         /* 0x80: RCC spread spectrum clock generation register */
    __vo uint32_t PLLI2SCFGR;    /* 0x84: RCC PLLI2S configuration register */
} RCC_RegDef_t;




#define GPIOA   ((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB   ((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC   ((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD   ((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE   ((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF   ((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG   ((GPIO_RegDef_t*)GPIOG_BASEADDR)
#define GPIOH   ((GPIO_RegDef_t*)GPIOH_BASEADDR)
#define GPIOI   ((GPIO_RegDef_t*)GPIOI_BASEADDR)


#define RCC 				((RCC_RegDef_t*)RCC_BASEADDR)


/* Clock enable Macros for GPIOx Peripherals */
#define GPIOA_PCLK_EN()     ( RCC->AHB1ENR |= (1 << 0) )
#define GPIOB_PCLK_EN()     ( RCC->AHB1ENR |= (1 << 1) )
#define GPIOC_PCLK_EN()     ( RCC->AHB1ENR |= (1 << 2) )
#define GPIOD_PCLK_EN()     ( RCC->AHB1ENR |= (1 << 3) )
#define GPIOE_PCLK_EN()     ( RCC->AHB1ENR |= (1 << 4) )
#define GPIOF_PCLK_EN()     ( RCC->AHB1ENR |= (1 << 5) )
#define GPIOG_PCLK_EN()     ( RCC->AHB1ENR |= (1 << 6) )
#define GPIOH_PCLK_EN()     ( RCC->AHB1ENR |= (1 << 7) )
#define GPIOI_PCLK_EN()     ( RCC->AHB1ENR |= (1 << 8) )

/* Clock disable Macros for GPIOx Peripherals */
#define GPIOA_PCLK_DI()     ( RCC->AHB1ENR &= ~(1 << 0) )
#define GPIOB_PCLK_DI()     ( RCC->AHB1ENR &= ~(1 << 1) )
#define GPIOC_PCLK_DI()     ( RCC->AHB1ENR &= ~(1 << 2) )
#define GPIOD_PCLK_DI()     ( RCC->AHB1ENR &= ~(1 << 3) )
#define GPIOE_PCLK_DI()     ( RCC->AHB1ENR &= ~(1 << 4) )
#define GPIOF_PCLK_DI()     ( RCC->AHB1ENR &= ~(1 << 5) )
#define GPIOG_PCLK_DI()     ( RCC->AHB1ENR &= ~(1 << 6) )
#define GPIOH_PCLK_DI()     ( RCC->AHB1ENR &= ~(1 << 7) )
#define GPIOI_PCLK_DI()     ( RCC->AHB1ENR &= ~(1 << 8) )

/* Clock enable Macros for I2Cx Peripherals */
#define I2C1_PCLK_EN()      ( RCC->APB1ENR |= (1 << 21) )









/*
 * Macros to reset GPIOx peripherals
 */

#define GPIOA_REG_RESET()  				do{(RCC->AHB1RSTR |= (1 << 0)) ;   (RCC->AHB1RSTR &= ~(1 << 0)); }while(0)
#define GPIOB_REG_RESET()  				do{(RCC->AHB1RSTR |= (1 << 1)) ;   (RCC->AHB1RSTR &= ~(1 << 1)); }while(0)
#define GPIOC_REG_RESET()  				do{(RCC->AHB1RSTR |= (1 << 2)) ;   (RCC->AHB1RSTR &= ~(1 << 2)); }while(0)
#define GPIOD_REG_RESET()  				do{(RCC->AHB1RSTR |= (1 << 3)) ;   (RCC->AHB1RSTR &= ~(1 << 3)); }while(0)
#define GPIOE_REG_RESET()  				do{(RCC->AHB1RSTR |= (1 << 4)) ;   (RCC->AHB1RSTR &= ~(1 << 4)); }while(0)
#define GPIOF_REG_RESET()  				do{(RCC->AHB1RSTR |= (1 << 5)) ;   (RCC->AHB1RSTR &= ~(1 << 5)); }while(0)
#define GPIOG_REG_RESET()  				do{(RCC->AHB1RSTR |= (1 << 6)) ;   (RCC->AHB1RSTR &= ~(1 << 6)); }while(0)
#define GPIOH_REG_RESET()  				do{(RCC->AHB1RSTR |= (1 << 7)) ;   (RCC->AHB1RSTR &= ~(1 << 7)); }while(0)
#define GPIOI_REG_RESET()  				do{(RCC->AHB1RSTR |= (1 << 8)) ;   (RCC->AHB1RSTR &= ~(1 << 8)); }while(0)






// Some generic macros
#define ENABLE 			1
#define DISABLE 		0
#define SET 			ENABLE
#define RESET 			DISABLE
#define GPIO_PIN_SET    SET
#define GPIO_PIN_RESET  RESET


























#include "stm32f407xx_gpio_driver.h"
#endif /* INC_STM32F407XX_H_ */
