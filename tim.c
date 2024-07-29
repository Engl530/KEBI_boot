#include "stm32f0xx.h"
#include "tim.h"
//----------------------------------------------------
void initTIM(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM14EN;
	TIM14->CNT = 1;
	TIM14->PSC = 48000; //������� ������������ 1��� 
	TIM14->ARR = 501; //������� �� 500, ���������� ������� ��� � 500��
	TIM14->CR1 |= TIM_CR1_CEN;
}
//----------------------------------------------------
void deinitTIM(void)
{
	RCC->APB1ENR &= ~RCC_APB1ENR_TIM14EN;
	TIM14->CR1 = 0;
	TIM14->CNT = 0;
	TIM14->PSC = 0;
	TIM14->ARR = 0xFFFF; //reset value
	
}
//----------------------------------------------------
