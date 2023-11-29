/* Defines -----------------------------------------------------------*/
#ifndef F_CPU
# define F_CPU 16000000  // CPU frequency in Hz required for UART_BAUD_SELECT
#endif

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include <uart.h>           // Peter Fleury's UART library
#include <stdlib.h>         // C library. Needed for number conversions
#include <adc.h>
#include <oled.h>

/* Function definitions ----------------------------------------------*/
int main(void)
{
    uart_init(UART_BAUD_SELECT(115200, F_CPU));
    ADC_init();
    // TWI
    twi_init();

    // UART
    // uart_init(UART_BAUD_SELECT(115200, F_CPU));
    oled_init(OLED_DISP_ON);
    oled_clrscr();
    
    TIM0_OVF_1MS
    TIM0_OVF_ENABLE
    

    TIM1_OVF_2S
    TIM1_OVF_ENABLE

    sei();

    while (1)
    {
        /* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines ISRs */
    }

    return 0;
}

/* Interrupt service routines ----------------------------------------*/
ISR(TIMER1_OVF_vect)
{
    // Start ADC conversion
    uint16_t value = ADC_read(0);
}

ISR(TIMER0_OVF_vect)
{
    uint16_t value, x;
    char string[8];  // Increase the size to hold three digits and the null terminator

    // Read converted value
    value = ADC_read();

    // Convert "value" to "string" and display it
    x = (value * 100 / 1023);
    x = 100 - x;
    itoa(x, string, 10);
    oled_gotoxy(2, 2);
    oled_puts(string);
    oled_puts(".");
}

ISR(ADC_vect)
{
    uint16_t value, x;
    char string[8];  // Increase the size to hold three digits and the null terminator

    // Read converted value
    value = ADC_read();

    // Convert "value" to "string" and display it
    x = (value * 100 / 1023);
    x = 100 - x;
    itoa(x, string, 10);
    uart_puts(string);
    uart_puts(" ");
    oled_gotoxy(2, 2);
    oled_puts(string);
    oled_puts(".");

}
