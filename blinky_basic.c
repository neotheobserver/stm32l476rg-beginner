#define PERIPH_BASE (0x40000000UL)

#define AHB1PERIPH_OFFSET (0x00020000UL)
#define AHB1PERIPH_BASE (PERIPH_BASE + AHB1PERIPH_OFFSET)

#define RCC_OFFSET (0x1000UL)
#define RCC_BASE (AHB1PERIPH_BASE + RCC_OFFSET)

#define AHB2PERIPH_OFFSET (0x08000000UL)
#define AHB2PERIPH_BASE (PERIPH_BASE + AHB2PERIPH_OFFSET)

#define GPIOA_OFFSET (0x00)
#define GPIOA_BASE (AHB2PERIPH_BASE + GPIOA_OFFSET)

#define AHB2ENR_OFFSET (0x4C)
#define RCC_AHB2ENR (*(volatile unsigned int *)(RCC_BASE + AHB2ENR_OFFSET))

#define MODER_OFFSET (0x00U)
#define GPIOA_MODER (*(volatile unsigned int *)(GPIOA_BASE + MODER_OFFSET))

#define ODR_OFFSET (0x14U)
#define GPIOA_ODR (*(volatile unsigned int *)(GPIOA_BASE + ODR_OFFSET))

#define GPIOAEN		(1U)

#define PIN5		(1U << 5)
#define LED_PIN		PIN5

int main(void){
	//Enable clock access for GPIOA
	RCC_AHB2ENR |= GPIOAEN;

	//Set PIN5 as output pin
	GPIOA_MODER |= (1U << 10); //set 10th bit on
	GPIOA_MODER &= ~(1U << 11); //set 11th bit off

	while(1){
		GPIOA_ODR ^= LED_PIN;
		for (int i = 0; i < 100000; i++);
	}
}
