/*
 * systick.h
 *
 *  Created on: Aug 31, 2024
 *      Author: pedro
 */
#include <stdint.h>
#ifndef SYSTICK_H_
#define SYSTICK_H_

void systick_init(void);
void delay_ms(uint32_t ms);

#endif /* SYSTICK_H_ */
