#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include "stm32f1xx.h"

void delay_ms(uint32_t ms) {
    SysTick->LOAD = 8000 - 1; // Para 1 ms delay, considerando 8 MHz clock
    SysTick->VAL = 0;
    SysTick->CTRL = 5; // Habilita o contador

    for (uint32_t i = 0; i < ms; i++) {
        while (!(SysTick->CTRL & 0x10000)); // Espera até que a flag de contagem seja definida
    }

    SysTick->CTRL = 0; // Desabilita o contador
}

/*
 * EXTI15-10 external interrupt handler
 */
void EXTI15_10_IRQHandler(void)
{
	//TRATAMENTO DE INTERRUPÇÂO PINO C13
	if (EXTI->PR & EXTI_PR_PR13){   // Verifica se a interrupção é do pino PC13
		EXTI->PR |= EXTI_PR_PR13; // Limpa a flag de interrupção para PC13
		// Alterna o estado do LED no pino PA8
	    if(GPIOA->ODR & GPIO_ODR_ODR8){
	        GPIOA->ODR &= ~GPIO_ODR_ODR8; // Apaga o LED
	    }
	    else{
	        GPIOA->ODR |= GPIO_ODR_ODR8;  // Acende o LED
	    }
	}

	//TRATAMENTO DE INTERRUPÇÂO PINO C14
	if (EXTI->PR & EXTI_PR_PR14){
		EXTI->PR |= EXTI_PR_PR14;
		// Alterna o estado do LED no pino PA9
		if (GPIOA->ODR & GPIO_ODR_ODR9){
			GPIOA->ODR &= ~GPIO_ODR_ODR9; // Apaga o LED
		}
		else{
			GPIOA->ODR |= GPIO_ODR_ODR9;  // Acende o LED
		}
	}

	//TRATAMENTO DE INTERRUPÇÂO PINO C15
	if (EXTI->PR & EXTI_PR_PR15){
			EXTI->PR |= EXTI_PR_PR15;
			// Alterna o estado do LED no pino PA10
			if (GPIOA->ODR & GPIO_ODR_ODR10){
				GPIOA->ODR &= ~GPIO_ODR_ODR10; // Apaga o LED
			}
			else{
				GPIOA->ODR |= GPIO_ODR_ODR10;  // Acende o LED
			}
		}

}

int main(void)
{
	RCC->APB2ENR |= (1 << 2) | (1 << 4);

	// Make GPIOC Pi13, Pin14 and pin15 input
	GPIOC->CRH &= 0x000FFFFF;
	GPIOC->CRH |= 0x88800000;

	//Enable GPIO Pin13, Pin14 and pin15 pull-up
	GPIOC->ODR = 0x0000E000;

	// Make GPIOA Pin8, pin9, pin10 output
	GPIOA->CRH &= 0xFFFFF000;
	GPIOA->CRH |= 0x00000888;


	// Reset GPIOA Pin8, pin9, pin10, and pin 11
	GPIOA->ODR &= ~(1 << 8);
	GPIOA->ODR &= ~(1 << 9);
	GPIOA->ODR &= ~(1 << 10);

	__disable_irq();

	// Since we will use Alternate Function (EXTI) we need to enable the
	//   clock for that module. Bit0 in RCC APB2ENR register
	RCC->APB2ENR |= (1 << 0); // AFIO Clock enable

	// EXTI13 can be configured for each GPIO module.
	//   EXTICR1: 0b XXXX XXXX XXXX 0001
	//               pin3 pin2 pin1 pin0
	//
	//   Writing a 0b0001 to pin0 location ties PC13 to EXTI13
	AFIO->EXTICR[3] |= AFIO_EXTICR4_EXTI13_PC | AFIO_EXTICR4_EXTI14_PC | AFIO_EXTICR4_EXTI15_PC;

	// We mask the used external interrupt numbers.
	EXTI->IMR |= (EXTI_IMR_IM13 | EXTI_IMR_IM14 | EXTI_IMR_IM15);

	// Next we choose either falling edge trigger (FTSR) or falling edge trigger (FTSR)
	EXTI->RTSR |= (EXTI_RTSR_TR13 | EXTI_RTSR_TR14 | EXTI_RTSR_TR15);

	// Set Priority for each interrupt request
	// STM32F103 supports 4-bit priority level (highest 4-bits are implemented)
	NVIC_SetPriority(EXTI15_10_IRQn, 0);

	// Enable EXTI15_10 interrupt on NVIC
	NVIC_EnableIRQ(EXTI15_10_IRQn);

	__enable_irq();

	GPIOA->ODR |= (1 << 8);
	GPIOA->ODR |= (1 << 9);
	GPIOA->ODR |= (1 << 10);

	while(1)
	{

		// Delay simples (não precisa ser preciso)
		delay_ms(500);

	}
}
