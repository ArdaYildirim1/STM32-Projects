

#ifndef MAIN_H_
#define MAIN_H_

#include <stdint.h>

#define ADDR_AHB1ENR_REG    (0x40023830UL)
#define ADDR_GPIOD_MODE     (0x40020C00UL)
#define ADDR_GPIOD_ODR      (0x40020C14UL)
#define ADDR_GPIOA_MODE     (0x40020000UL)
#define ADDR_GPIOA_IDR      (0x40020010UL)

#define CLOCK_ENABLE        (1)
#define MODE_CONF_OUTPUT    (1)
#define MODE_CONF_INPUT     (0)
#define PIN_STATE_HIGH      (1)
#define PIN_STATE_LOW       (0)

#define DELAY_COUNT         (150000UL)



typedef struct
{
	uint32_t gpioa_en      : 1;
	uint32_t gpiob_en      : 1;
	uint32_t gpioc_en      : 1;
	uint32_t gpiod_en      : 1;
	uint32_t gpioe_en      : 1;
	uint32_t gpiof_en      : 1;
	uint32_t gpiog_en      : 1;
	uint32_t gpioh_en      : 1;
	uint32_t gpioi_en      : 1;
	uint32_t gpioj_en      : 1;
	uint32_t gpiok_en      : 1;
	uint32_t res_1         : 1;
	uint32_t crc_en        : 1;
	uint32_t reserved_1    : 3;
	uint32_t reserved_2    : 2;
	uint32_t bkpsram_en    : 1;
	uint32_t res_2         : 1;
	uint32_t ccmdataram_en : 1;
	uint32_t dma1_en       : 1;
	uint32_t dma2_en       : 1;
	uint32_t dma2d_en      : 1;
	uint32_t res_3         : 1;
	uint32_t ethmac_en     : 1;
	uint32_t ethmactx_en   : 1;
	uint32_t ethmacrx_en   : 1;
	uint32_t ethmacptp_en : 1;
	uint32_t otghs_en      : 1;
	uint32_t otghsulpi_en  : 1;
	uint32_t reserved_3    : 1;

}RCC_AHB1ENR_t;

typedef struct
{

	   uint32_t pin_0		:2;
	   uint32_t pin_1		:2;
	   uint32_t pin_2		:2;
	   uint32_t pin_3		:2;
	   uint32_t pin_4		:2;
	   uint32_t pin_5		:2;
	   uint32_t pin_6		:2;
	   uint32_t pin_7		:2;
	   uint32_t pin_8		:2;
	   uint32_t pin_9		:2;
	   uint32_t pin_10		:2;
	   uint32_t pin_11		:2;
	   uint32_t pin_12		:2;
	   uint32_t pin_13		:2;
	   uint32_t pin_14		:2;
	   uint32_t pin_15		:2;

}GPIOx_MODE_t;

typedef struct
{
   uint32_t pin_0		:1;
   uint32_t pin_1		:1;
   uint32_t pin_2		:1;
   uint32_t pin_3		:1;
   uint32_t pin_4		:1;
   uint32_t pin_5		:1;
   uint32_t pin_6		:1;
   uint32_t pin_7		:1;
   uint32_t pin_8		:1;
   uint32_t pin_9		:1;
   uint32_t pin_10		:1;
   uint32_t pin_11		:1;
   uint32_t pin_12		:1;
   uint32_t pin_13		:1;
   uint32_t pin_14		:1;
   uint32_t pin_15		:1;
   uint32_t reserved	:16;
}GPIOx_ODR_t;

typedef struct
{
   uint32_t pin_0		:1;
   uint32_t pin_1		:1;
   uint32_t pin_2		:1;
   uint32_t pin_3		:1;
   uint32_t pin_4		:1;
   uint32_t pin_5		:1;
   uint32_t pin_6		:1;
   uint32_t pin_7		:1;
   uint32_t pin_8		:1;
   uint32_t pin_9		:1;
   uint32_t pin_10		:1;
   uint32_t pin_11		:1;
   uint32_t pin_12		:1;
   uint32_t pin_13		:1;
   uint32_t pin_14		:1;
   uint32_t pin_15		:1;
   uint32_t reserved	:16;
}GPIOx_IDR_t;


#define RCC_BASE    0x40023800
#define GPIOA_BASE  0x40020000
#define GPIOD_BASE  0x40020C00


#endif /* MAIN_H_ */
