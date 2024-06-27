#include "stm32f10x.h"

void LED_Init(void) {
  // Enable GPIOC clock
  RCC->APB2ENR |= (1<<4);

  // Configure PC13 as push-pull output
  GPIOC->CRH &= ~GPIO_CRH_CNF13;  // Clear CNF13 bits
  GPIOC->CRH |= (	(1<<20)	|	(1<<21) ); // Output mode, max speed 2 MHz
	GPIOC->CRH &= ~((1<<22)	|	(1<<23)	);
	
	// Ensure the LED is off initially
	GPIOC->BSRR = (1 << (13 + 16));  // Set PC13 high (LED off)
}

void TIM2_Init(void) {
    // Enable TIM2 clock
    RCC->APB1ENR |= (1<<0);

    // Configure TIM2
    TIM2->PSC = 7999;  // Prescaler value (assuming 72 MHz APB1 clock, gives 9kHz timer clock)
    TIM2->ARR = 17999;  // Auto-reload value (gives 2 second period with above settings)

    // Configure Capture/Compare
    TIM2->CCR1 = 19999;  // Set compare value for 2 seconds
    TIM2->CCMR1 |= (1 << 4) | (1 << 5); // Set output compare mode to toggle on match
    TIM2->CCER |= (1<<0);  // Enable capture/compare channel 1

    // Enable capture/compare interrupt (not needed for polling)
    // TIM2->DIER |= TIM_DIER_CC1IE;

    // Enable TIM2
    TIM2->CR1 |= (1<<0);		//enable counter CEN bit
}

int main(void) {
    LED_Init();
    TIM2_Init();

    while (1) {
        // Polling loop to check if the capture/compare interrupt flag is set
        if (TIM2->SR & TIM_SR_CC1IF) {
					
            TIM2->SR &= ~(1<<1);  // Clear the capture/compare interrupt flag
            GPIOC->ODR ^= (1 << 13);    // Toggle the LED
        }
    }
}
