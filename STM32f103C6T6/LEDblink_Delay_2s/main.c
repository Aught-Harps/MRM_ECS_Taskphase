#include "stm32f10x.h"

// Variable to store millisecond ticks
volatile int msTicks = 0;

void delayMs(int ms);
void LED_Init(void);
void SysTick_Handler(void);

int main(void) {
    // Initialize the LED
    LED_Init();

    // Configure SysTick timer for 1ms interrupts
    if (SysTick_Config(SystemCoreClock / 1000)) {
        // Handle error
        while (1);
    }

    while (1) {
        // Turn on the LED
        GPIOC->BSRR = (1 << 13);
        delayMs(2000);  // Delay for 2 seconds

        // Turn off the LED
        GPIOC->BSRR = (1 << (13 + 16));
        delayMs(2000);  // Delay for 2 seconds
    }
}

void delayMs(int ms) {
    msTicks = 0;  // Reset msTicks
    while (msTicks < ms);  // Wait until msTicks reaches the desired delay
}

void SysTick_Handler(void) {
    msTicks++;  // Increment msTicks every millisecond
}

void LED_Init(void) {
    // Enable GPIOC clock
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

    // Configure PC13 as push-pull output
    GPIOC->CRH &= ~GPIO_CRH_CNF13;  // Clear CNF13 bits
    GPIOC->CRH |= GPIO_CRH_MODE13_1; // Output mode, max speed 2 MHz
    GPIOC->CRH &= ~GPIO_CRH_MODE13_0; // MODE13[1:0] = 10 (Output mode, max speed 2 MHz)

    // Ensure the LED is off initially
    GPIOC->BSRR = (1 << (13 + 16));  // Set PC13 high (LED off)
}
