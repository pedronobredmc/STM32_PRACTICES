/*
 * interrupt.c
 *
 *  Created on: Aug 31, 2024
 *      Author: pedro
 */
#include <stdint.h>
#include "stm32f1xx.h"
#include "gpio.h"
#include "systick.h"
#include "interrupt.h"

void init_pin_interrupt(unsigned short port, unsigned short pin, borda trigger_type, uint8_t priority, IRQn_Type type)
{
	__disable_irq();
	RCC->APB2ENR |= (1 << 0); // AFIO Clock enable

	if (pin < 4) {
	    AFIO->EXTICR[0] &= ~(0xF << (pin * 4));
	    AFIO->EXTICR[0] |= ((port == 1 ? 0 : port == 2 ? 1 : port == 3 ? 2 : 3) << (pin * 4));
	} else if (pin < 8) {
	    AFIO->EXTICR[1] &= ~(0xF << ((pin - 4) * 4));
	    AFIO->EXTICR[1] |= ((port == 1 ? 0 : port == 2 ? 1 : port == 3 ? 2 : 3) << ((pin - 4) * 4));
	} else if (pin < 12) {
		AFIO->EXTICR[2] &= ~(0xF << ((pin - 8) * 4));
	    AFIO->EXTICR[2] |= ((port == 1 ? 0 : port == 2 ? 1 : port == 3 ? 2 : 3) << ((pin - 8) * 4));
	} else {
		AFIO->EXTICR[3] &= ~(0xF << ((pin - 12) * 4));
	    AFIO->EXTICR[3] |= ((port == 1 ? 0 : port == 2 ? 1 : port == 3 ? 2 : 3 ) << ((pin - 12) * 4));
	}

	EXTI->IMR |= (1 << pin);

	if (trigger_type == 0) { // Rising edge
	       	EXTI->RTSR |= (1 << pin);
	} else if (trigger_type == 1) { // Falling edge
	        EXTI->FTSR |= (1 << pin);
	} else { // Both edges
	        EXTI->RTSR |= (1 << pin);
	        EXTI->FTSR |= (1 << pin);
	}

	NVIC_SetPriority(type, priority);
	NVIC_EnableIRQ(type);

	__enable_irq();
}


void EXTI0_IRQHandler(void)
{
	EXTI->PR |= EXTI_PR_PR0; // Limpa a flag de interrupção para P0
	//Lógica da interrupção

}
void EXTI1_IRQHandler(void)
{
	EXTI->PR |= EXTI_PR_PR1; // Limpa a flag de interrupção para P1
	//Lógica da interrupção

}
void EXTI2_IRQHandler(void)
{
	EXTI->PR |= EXTI_PR_PR2; // Limpa a flag de interrupção para P2
	//Lógica da interrupção

}
void EXTI3_IRQHandler(void)
{
	EXTI->PR |= EXTI_PR_PR3; // Limpa a flag de interrupção para P3
	//Lógica da interrupção

}
void EXTI4_IRQHandle(void)
{
	EXTI->PR |= EXTI_PR_PR4; // Limpa a flag de interrupção para P4
	//Lógica da interrupção

}

void EXTI9_5_IRQHandler(void)
{
	if (EXTI->PR & EXTI_PR_PR5){   // Verifica se a interrupção é do pino P10
		EXTI->PR |= EXTI_PR_PR5; // Limpa a flag de interrupção para P10
		//Lógica da interrupção
	}

	//TRATAMENTO DE INTERRUPÇÂO PINO 11
	if (EXTI->PR & EXTI_PR_PR6){   // Verifica se a interrupção é do pino P11
		EXTI->PR |= EXTI_PR_PR6; // Limpa a flag de interrupção para P11
		//Lógica da interrupção
	}


	//TRATAMENTO DE INTERRUPÇÂO PINO 12
	if (EXTI->PR & EXTI_PR_PR7){   // Verifica se a interrupção é do pino P13
		EXTI->PR |= EXTI_PR_PR7; // Limpa a flag de interrupção para P13
		//Lógica da interrupção
	}

	//TRATAMENTO DE INTERRUPÇÂO PINO 13
	if (EXTI->PR & EXTI_PR_PR8){   // Verifica se a interrupção é do pino P13
		EXTI->PR |= EXTI_PR_PR8; // Limpa a flag de interrupção para P13
		//Lógica da interrupção
	}

	//TRATAMENTO DE INTERRUPÇÂO PINO 14
	if (EXTI->PR & EXTI_PR_PR9){	// Verifica se a interrupção é do pino P14
		EXTI->PR |= EXTI_PR_PR9; // Limpa a flag de interrupção para P14
		//Lógica da interrupção
	}

}





void EXTI15_10_IRQHandler(void)
{
	//TRATAMENTO DE INTERRUPÇÂO PINO 10
	if (EXTI->PR & EXTI_PR_PR10){   // Verifica se a interrupção é do pino P10
		EXTI->PR |= EXTI_PR_PR10; // Limpa a flag de interrupção para P10
		//Lógica da interrupção
		toggle_GP(PA,8);
	}

	//TRATAMENTO DE INTERRUPÇÂO PINO 11
	if (EXTI->PR & EXTI_PR_PR11){   // Verifica se a interrupção é do pino P11
		EXTI->PR |= EXTI_PR_PR11; // Limpa a flag de interrupção para P11
		//Lógica da interrupção
	}


	//TRATAMENTO DE INTERRUPÇÂO PINO 12
	if (EXTI->PR & EXTI_PR_PR12){   // Verifica se a interrupção é do pino P13
		EXTI->PR |= EXTI_PR_PR12; // Limpa a flag de interrupção para P13
		//Lógica da interrupção
	}

	//TRATAMENTO DE INTERRUPÇÂO PINO 13
	if (EXTI->PR & EXTI_PR_PR13){   // Verifica se a interrupção é do pino P13
		EXTI->PR |= EXTI_PR_PR13; // Limpa a flag de interrupção para P13
		//Lógica da interrupção
		toggle_GP(PA,8);
	}

	//TRATAMENTO DE INTERRUPÇÂO PINO 14
	if (EXTI->PR & EXTI_PR_PR14){	// Verifica se a interrupção é do pino P14
		EXTI->PR |= EXTI_PR_PR14; // Limpa a flag de interrupção para P14
		//Lógica da interrupção
		toggle_GP(PA,9);
	}

	//TRATAMENTO DE INTERRUPÇÂO PINO 15
	if (EXTI->PR & EXTI_PR_PR15){	// Verifica se a interrupção é do pino P15
		EXTI->PR |= EXTI_PR_PR15; // Limpa a flag de interrupção para P15
		//Lógica da interrupção
		toggle_GP(PA,10);
	}

}
