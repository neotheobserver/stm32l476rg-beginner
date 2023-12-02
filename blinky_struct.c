#define PERIPH_BASE (0x40000000UL)

#define AHB1PERIPH_OFFSET (0x00020000UL)
#define AHB1PERIPH_BASE (PERIPH_BASE + AHB1PERIPH_OFFSET)

#define RCC_OFFSET (0x1000UL)
#define RCC_BASE (AHB1PERIPH_BASE + RCC_OFFSET)

#define AHB2PERIPH_OFFSET (0x08000000UL)
#define AHB2PERIPH_BASE (PERIPH_BASE + AHB2PERIPH_OFFSET)

#define GPIOA_OFFSET (0x00)
#define GPIOA_BASE (AHB2PERIPH_BASE + GPIOA_OFFSET)

#define GPIOAEN		(1U)

#define PIN5		(1U << 5)
#define LED_PIN		PIN5

#define __IO volatile
#include <stdint.h>

typedef struct{
	__IO uint32_t MODER;
	__IO uint32_t OTYPER;
	__IO uint32_t OSPEEDR;
	__IO uint32_t PUPDR;
	__IO uint32_t IDR;
	__IO uint32_t ODR;
	__IO uint32_t BSRR;
	__IO uint32_t LCKR;
	__IO uint32_t AFR[2];
	__IO uint32_t BRR;
	__IO uint32_t ASCR;
}GPIO_TypeDef;

typedef struct{
	// 16 registers before the register we need
	// +3 reserved address
	volatile uint32_t REGISTERS[19];
	volatile uint32_t AHB2ENR;
}RCC_TypeDef;

#define RCC  ((RCC_TypeDef*)RCC_BASE)
#define GPIOA ((GPIO_TypeDef*)GPIOA_BASE)

int main(void){
	//Enable clock access for GPIOA
	RCC->AHB2ENR |= GPIOAEN;

	//Set PIN5 as output pin
	GPIOA->MODER |= (1U << 10); //set 10th bit on
	GPIOA->MODER &= ~(1U << 11); //set 11th bit off

	while(1){
		GPIOA->ODR ^= LED_PIN;
		for (int i = 0; i < 100000; i++);
	}
}

