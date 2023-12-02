#include "stm32l476xx.h"

#define GPIOAEN (1U)
#define GPIOCEN (1U << 2)

#define PIN5 (1U << 5)
#define PIN13 (1U << 13)

int main(void){

	//Enable clock for GPIOA and GPIOC
	RCC->AHB2ENR |= GPIOAEN | GPIOCEN;

	//set to output bit 10 to 1 and 11 to 0
	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);

	// set bit 26 and 27 to 0 for input
	GPIOC->MODER &= ~(3U << 26);

	while(1){
		if (GPIOC->IDR & PIN13){
			GPIOA->BSRR = PIN5;
		} else {
			GPIOA->BSRR = (1U << 21);
		}
	}
}
