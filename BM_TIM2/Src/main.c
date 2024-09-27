#include <stdint.h>

#if !defined(_SOFT_FP) && defined(_ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include "stm32f1xx.h"

/*
 * TIM2 interrupt handler
 */
int state = 0;
int blink_count = 0;
int blink_state=1;


void led_off(){
	GPIOA->ODR &= ~(1 << 0);
	GPIOA->ODR &= ~(1 << 1);
	GPIOA->ODR &= ~(1 << 2);
}
void TIM2_IRQHandler(void)
{
    if(TIM2->SR & TIM_SR_UIF)
    {
        // Alternar as combinações de cores
        if(blink_state==0){
        	led_off();
        	blink_state=1;
        }else{
        	blink_count++;
        	switch(state)
        	        {
        	            case 0:  // Vermelho
        	            	led_off();
        	                GPIOA->ODR |=  (1 << 0);
        	                GPIOA->ODR &= ~(1 << 1);
        	                GPIOA->ODR &= ~(1 << 2);
        	                blink_state=0;
        	                break;
        	            case 1:  // Verde
        	            	led_off();
        	                GPIOA->ODR &= ~(1 << 0);
        	                GPIOA->ODR |=  (1 << 1);
        	                GPIOA->ODR &= ~(1 << 2);
        	                blink_state=0;
        	                break;
        	            case 2:  // Azul
        	            	led_off();
        	                GPIOA->ODR &= ~(1 << 0);
        	                GPIOA->ODR &= ~(1 << 1);
        	                GPIOA->ODR |=  (1 << 2);
        	                blink_state=0;
        	                break;
        	            case 3:  // Amarelo (Vermelho + Verde)
        	            	led_off();
        	                GPIOA->ODR |=  (1 << 0);
        	                GPIOA->ODR |=  (1 << 1);
        	                GPIOA->ODR &= ~(1 << 2);
        	                blink_state=0;
        	                break;
        	            case 4:  // Ciano (Verde + Azul)
        	            	led_off();
        	                GPIOA->ODR &= ~(1 << 0);
        	                GPIOA->ODR |=  (1 << 1);
        	                GPIOA->ODR |=  (1 << 2);
        	                blink_state=0;
        	                break;
        	            case 5:  // Roxo (Vermelho + Azul)
        	            	led_off();
        	                GPIOA->ODR |=  (1 << 0);
        	                GPIOA->ODR &= ~(1 << 1);
        	                GPIOA->ODR |=  (1 << 2);
        	                blink_state=0;
        	                break;
        	            case 6:  // Branco (Vermelho + Verde + Azul)
        	            	led_off();
        	                GPIOA->ODR |=  (1 << 0);
        	                GPIOA->ODR |=  (1 << 1);
        	                GPIOA->ODR |=  (1 << 2);
        	                blink_state=0;
        	                break;

        	        }
        	if (blink_count >= 2){
        		blink_count = 0;
        		state = (state + 1) % 7;  // Alterna entre 0 e 6 para as cores
        	}

        }



        TIM2->SR &= ~TIM_SR_UIF;  // Limpar a flag de interrupção
    }
}

int main(void)
{
    // Habilitar o clock para GPIOA (para os LEDs RGB)
    RCC->APB2ENR |= (1 << 2);

    // Configurar GPIOA para saída (pinos 0, 1, e 2 para RGB)
    GPIOA->CRL &= ~(0xFFF);  // Limpar configurações anteriores para PA0, PA1 e PA2
    GPIOA->CRL |=  (0x333);  // Configurar PA0, PA1 e PA2 como saída push-pull de 2 MHz

    // Enable clock access to timer2
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    // Configure timer2
    TIM2->PSC = 8000 - 1; 	// 8000000 / 8000 = 1000 i.e. 1ms
    TIM2->ARR = 500 - 1; 	// Contar até 500 ms (para piscar a cada meio segundo)

    // Set UIE(Update interrupt enable) bit to enable timer interrupt
    TIM2->DIER |= TIM_DIER_UIE;

    // Enable timer2 interrupt in NVIC
    NVIC_EnableIRQ(TIM2_IRQn);

    // Enable the timer
    TIM2->CR1 |= TIM_CR1_CEN;

    while(1)
    {
        // O LED RGB piscará automaticamente devido ao timer2 e a interrupção TIM2_IRQHandler
    }
}

