#include "stm32f0xx.h"
#include "gpio.h"
//	GPIO initialization
//----------------------------------------------------
void initGPIO(void)
{
	//	enable PORTF bus
	RCC->AHBENR |= RCC_AHBENR_GPIOFEN;

	//	PORTF0 - ouput
	GPIOF->MODER &= ~GPIO_MODER_MODER0;
	GPIOF->MODER |= GPIO_MODER_MODER0_0; //	MODER0[1:0] = 01 - General purpose output mode
	GPIOF->OTYPER &= ~GPIO_OTYPER_OT_0; //	OTYPER0 = 0 - Output push-pull
	GPIOF->OSPEEDR &= ~GPIO_OSPEEDR_OSPEEDR0; //	OSPEEDR0[1:0] = 00 - Low speed
	GPIOF->PUPDR &= ~GPIO_PUPDR_PUPDR0; //	PUPDR0[1:0] = 00 - No pull-up, pull-down
	GPIOF->BSRR &= ~GPIO_BSRR_BS_0; //	BSRR0 = 1 - set bit

	
	//	enable PORTA bus
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	//	PORTA7 - ouput
	GPIOA->MODER &= ~GPIO_MODER_MODER7_1;
	GPIOA->MODER |= GPIO_MODER_MODER7_0; //	MODER0[1:0] = 01 - General purpose output mode
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT_7; //	OTYPER0 = 0 - Output push-pull
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR7_0; //	OSPEEDR0[1:0] = 11 - High speed
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR7_1; //	OSPEEDR0[1:0] = 11 - High speed
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR7_1;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR7_0; //	PUPDR0[1:0] = 00 - No pull-up, pull-down
	//GPIOA->BSRR |= GPIO_BSRR_BS_7; //	BSRR7 = 0 - reset bit
	GPIOA->ODR &= ~GPIO_ODR_7; //PA - reset driver disable
	
	//остановилс€ тут, сделать инит дл€ ножек юарта
	//	PORTA8 - TX; PORTA9 - RX
	GPIOA->MODER |= (GPIO_MODER_MODER9_1 | GPIO_MODER_MODER10_1); //PA9 & PA10 alt mode
	GPIOA->AFR[1] |= ((1<<GPIO_AFRH_AFSEL9_Pos) | (1<<GPIO_AFRH_AFSEL10_Pos)); // AF1 дл€ PA9 и PA10
}
//----------------------------------------------------
void deinitGPIO(void)
{
	GPIOF->PUPDR = 0;
	GPIOF->OSPEEDR = 0;
	GPIOF->OTYPER = 0;
	GPIOF->MODER = 0;
	RCC->AHBENR &= ~RCC_AHBENR_GPIOFEN;
	
	GPIOA->AFR[1] = 0;
	GPIOA->PUPDR = 0x24000000;
	GPIOA->OSPEEDR = 0x0C000000;
	GPIOA->OTYPER = 0;
	GPIOA->MODER = 0x28000000; //reset value
	RCC->AHBENR &= ~RCC_AHBENR_GPIOAEN;
}
//----------------------------------------------------
