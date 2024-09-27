/*
 * systic.c
 *
 *  Created on: Aug 31, 2024
 *      Author: pedro
 */

#include "systick.h"
#include "stm32f1xx.h"

void systick_init(void){

	SysTick->LOAD = 8000 - 1; // Para 1 ms delay, considerando 8 MHz clock
	SysTick->VAL = 0;
	SysTick->CTRL = 5; // Habilita o contador

}

/*void DelayMillis(void)
{
	SysTick->LOAD = 0x11940;
	SysTick->VAL = 0;
	while((SysTick->CTRL & 0x00010000) == 0);
}*/

void delay_ms(uint32_t ms)
{
	systick_init();
	for (uint32_t i = 0; i < ms; i++) {
	        while (!(SysTick->CTRL & 0x10000)); // Espera até que a flag de contagem seja definida
	    }
	SysTick->CTRL = 0; // Desabilita o contador
}
