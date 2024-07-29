#include "stm32f0xx.h"
#include "uart.h"
#include "main.h"

//----------------------------------------------------
void initUART(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	USART1->BRR = 480000/1152; //clock_freq = 48MHz boudrate=115200
	USART1->CR1 = USART_CR1_RE | USART_CR1_TE | USART_CR1_UE; 
}
//----------------------------------------------------
void deinitUART(void)
{
	USART1->CR1 = 0;
	USART1->BRR = 0;
	RCC->APB2ENR &= ~RCC_APB2ENR_USART1EN;
}
//----------------------------------------------------
void UART_Transmit(unsigned char data)
{
	//uint32_t isr;   // working copy of uart_SR register
	//isr = USART1->ISR;      //wait for Tx empty
	while(!(USART1->ISR & USART_ISR_TXE)){}
	GPIOA->ODR |= GPIO_ODR_7; //PA - set driver enable
	USART1->TDR = data;
	//isr = USART1->ISR;      //wait for Tx empty
	while(!(USART1->ISR & USART_ISR_TC)){}
	GPIOA->ODR &= ~GPIO_ODR_7; //PA - reset driver disable
} // End of UART_Transmit()
//----------------------------------------------------
unsigned char UART_Receive(unsigned char* ReceivedData)
{
  uint32_t isr;   // working copy of uart_SR register
  isr = USART1->ISR;      //wait for Rx full
  while(!(isr & 0x20 /*RXNE*/)) isr = USART1->ISR; //check if overrun or parity error
  if((isr & 0x08/*OR*/)||(isr & 0x01/*PE*/))
  {
    *ReceivedData = USART1->RDR ;        //receive data to clear error
    UART_Transmit(NACK);     //send NACK to host
    return 0;           //and return error
  }  
  *ReceivedData = USART1->RDR;     //receive data
  
  return 1;       //and return no error
} // End of UART_Receive()
//----------------------------------------------------
