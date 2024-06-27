#include "stm32f10x.h"

void LED_Init(void) {
    // Enable GPIOC clock
    RCC->APB2ENR |=(1<<4);

    // Configure PC13 as push-pull output
    GPIOC->CRH &= ~GPIO_CRH_CNF13;  // Clear CNF13 bits
    GPIOC->CRH |= (	(1<<20)	|	(1<<21) ); // Output mode, max speed 2 MHz
    GPIOC->CRH &= ~((1<<22)	|	(1<<23)	); // MODE13[1:0] = 10 (Output mode, max speed 2 MHz)

    // Ensure the LED is off initially
    GPIOC->BSRR = (1 << (13 + 16));  // Set PC13 high (LED off)
}


void TIM2_Delay_Init(void) {
    // Enable TIM2 clock
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    // Configure TIM2 to generate 1 Hz interrupts
    TIM2->PSC = 7999;  // Prescaler value (assuming 72 MHz APB1 clock, gives 10 kHz timer clock)
    TIM2->ARR = 19999; // Auto-reload value (gives 2 second period with above settings)

    // Start TIM2
    TIM2->CR1 |= 1<<0;		//enable CEN counter enable bit
}


void TIM2_Delay_Wait(void) {
    // Polling loop to wait for the delay to complete
    while (!(TIM2->SR & TIM_SR_UIF)); // Wait until update interrupt flag is set

    TIM2->SR &= ~(1<<0); // Clear the update interrupt flag
}


int main(void) {
	LED_Init();
	

    while (1) {
        // Main loop
			GPIOC->BSRR = (1 << 13);
			TIM2_Delay_Init();
			TIM2_Delay_Wait();
			
			GPIOC->BSRR = (1 << (13 + 16));
			TIM2_Delay_Init();
			TIM2_Delay_Wait();
    }
}
