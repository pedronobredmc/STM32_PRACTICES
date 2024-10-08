/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */


#include <stdint.h>

#define RCC_BASE_ADDRESS 										0x40021000 //Base address for RCC register
#define GPIOA_BASE_ADDRESS										0x40010800 //Base address for GPIOA
#define GPIOB_BASE_ADDRESS										0x40010C00 //Base address for GPIOB
#define GPIOC_BASE_ADDRESS										0x40011000 //Base address for GPIOC
#define APB2_OFFSET 											0x18 //Offset for apb2 periphal clock
#define GPIOx_CRH_OFFSET										0x04 //Offset for register high
#define GPIOx_ODR_OFFSET										0x0C //Offset for register output data
#define GPIOx_IDR_OFFSET										0x08 //Offset for register input data
#define GPIOx_CRL_OFFSET										0x00 //Offset for register input data


/*
#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif
*/

int main(void)
{
	//Define os ponteiros para os Registradores RCC_APB2ENR, GPIOB_CRH, GPIOA_CRH, GPIOA_ODR, GPIOV_IDR
		uint32_t *pRCC_APB2ENR = (uint32_t)0x40021018;
		uint32_t *pGPIOA_CRH = (uint32_t)0x40010804;
		uint32_t *pGPIOA_ODR = (uint32_t)0x4001080C;
		uint32_t *pGPIOC_CRH = (uint32_t)0x40011004;
		uint32_t *pGPIOC_IDR = (uint32_t)0x40011008;
		uint32_t *pGPIOC_ODR = (uint32_t)0x4001100C;

	//1. Habilita o clock da Porta A e C
		*pRCC_APB2ENR |= 0x00000014;
	//CNF8[3:2] = 00 e MODE8[1:0] = 10 //CNF9[7:6] = 00 e MODE9[5:4] = 10 //CNF10[11:10] = 00 e MODE10[9:8] = 10
	//2a. Reseta os bits [11:0]
		*pGPIOA_CRH &= 0xFFFFF000;
		*pGPIOC_CRH &= 0x000FFFFF;
	//2b. Seta o bit [1, 5 e 9]
		*pGPIOA_CRH |= 0x00000002;
		*pGPIOA_CRH |= 0x00000020;
		*pGPIOA_CRH |= 0x00000200;
	//2b. Seta o bit [23, 27 e 31]
		*pGPIOC_CRH |= 0x88800000; //AQUI
	//3. Seta o pino 8, 9 e 10 da Porta A (apaga o LED)
		*pGPIOA_ODR |= 0x00000000;
		// Habilita o pull up
		*pGPIOC_ODR |= 0x0000E000;
    /* Loop forever */
	for(;;){
			// Botão no pino C13 -> LED no pino A8
			if ((*pGPIOC_IDR & 0x00002000) == 0) // Verifica se o botão está pressionado
			{
				*pGPIOA_ODR |= 0x00000100; // acende led no pino A8

			}

			//apagar leds
			*pGPIOA_ODR &= ~0x00000100;

			// Botão no pino C14 -> LED no pino A9
			if ((*pGPIOC_IDR & 0x00004000) == 0) // Verifica se o botão está pressionado
			{
				*pGPIOA_ODR |= 0x00000200; // acende led no pino A10

			}

			//apagar leds
			*pGPIOA_ODR &= ~0x00000200;

			// Botão no pino C15 -> LED no pino A10
			if ((*pGPIOC_IDR & 0x00008000) == 0) // Verifica se o botão está pressionado
			{
				*pGPIOA_ODR |= 0x00000400; // acende led no pino A10
			}

			//apagar leds
			*pGPIOA_ODR &= ~0x00000400;
		}
}
