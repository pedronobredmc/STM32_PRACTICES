#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include "interrupt.h"


int main(void)
{
	init_GP(PA,8,OUT50,O_GP_PP); //Iniciando GPIO no pin A8 com saída de 50Hz
	init_GP(PA,9,OUT50,O_GP_PP); //Iniciando GPIO no pin A9 com saída de 50Hz
	init_GP(PA,10,OUT50,O_GP_PP); //Iniciando GPIO no pin A10 com saída de 50Hz

	init_GP(PC,14,IN,I_PP); //Iniciando GPIO no pin C14 com entrada
	init_GP(PC,15,IN,I_PP); //Iniciando GPIO no pin C15 com entrada
	init_GP(PB,10,IN,I_PP);

	init_pin_interrupt(PC, 14, RTSR, 0, EXTI15_10_IRQn); // Iniciando interrupão de borda de subida no pino C14
	init_pin_interrupt(PC, 15, RTSR, 0, EXTI15_10_IRQn); // Iniciando interrupão de borda de subida no pino C15
	init_pin_interrupt(PB, 10, RTSR, 0, EXTI15_10_IRQn);

	while(1){

	}

}
