/*
 * interrupt.h
 *
 *  Created on: Aug 31, 2024
 *      Author: pedro
 */
#include <stdint.h>
#include "stm32f1xx.h"
#include "gpio.h"
#include "systick.h"

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

typedef enum {
	RTSR,
	FTSR
}borda;

void init_pin_interrupt(unsigned short port, unsigned short pin, borda trigger_type, uint8_t priority, IRQn_Type type);
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);
void EXTI4_IRQHandle(void);
void EXTI9_5_IRQHandler(void);
void EXTI15_10_IRQHandler(void);

#endif /* INTERRUPT_H_ */
