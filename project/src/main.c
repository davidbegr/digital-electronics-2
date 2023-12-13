/***********************************************************************
 * 
 * Use USART unit and transmit data between ATmega328P and computer.
 * 
 * ATmega328P (Arduino Uno), 16 MHz, PlatformIO
 *
 * Copyright (c) 2018 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/


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
#include <oled.h>
#include <twi.h>            // I2C/TWI library for AVR-GCC

#define SENSOR_ADR 0x5c
#define SENSOR_TEMP_MEM 2

struct sensors {
    uint16_t x;
} sens;

/* Global variables --------------------------------------------------*/
// Declaration of "dht12" variable with structure "DHT_values_structure"
struct DHT_values_structure {
    uint8_t temp_int;
    uint8_t temp_dec;
    uint8_t checksum;
} dht12;

// Flag for printing new data from sensor
volatile uint8_t new_sensor_data = 0;
volatile uint8_t update = 0;
/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Use Timer/Counter1 and transmit UART data four times 
 *           per second.
 * Returns:  none
 **********************************************************************/
int main(void)
{
    char string[4];
    int x;
    oled_init(OLED_DISP_ON);
    oled_clrscr();
    twi_init();

    // Initialize USART to asynchronous, 8N1, 9600
     uart_init(UART_BAUD_SELECT(115200, F_CPU));
     // Configure Analog-to-Digital Convertion unit
    // Select ADC voltage reference to "AVcc with external capacitor at AREF pin"
    ADMUX = ADMUX | (1<<REFS0);
    // Select input channel ADC0 (voltage divider pin)
    ADMUX = ADMUX & ~(1<<MUX3 | 1<<MUX2 | 1<<MUX1 | 1<<MUX0);
    // Enable ADC module
    ADCSRA = ADCSRA | (1<<ADEN);
    // Enable conversion complete interrupt
    ADCSRA = ADCSRA | (1<<ADIE);
    // Set clock prescaler to 128
    ADCSRA = ADCSRA | (1<<ADPS2 | 1<<ADPS1 | 1<<ADPS0);

    // Configure 16-bit Timer/Counter1 to transmit UART data
    // Set prescaler to 262 ms and enable overflow interrupt
    TIM1_OVF_4SEC
    TIM1_OVF_ENABLE

    TIM0_OVF_16MS
    TIM0_OVF_ENABLE
   
    // Enables interrupts by setting the global interrupt mask
    sei();

    // Put strings to ringbuffer for transmitting via UART
    // uart_puts("Print one line... ");
    // uart_puts("done\r\n");

    // Infinite loop
    while (1)
    {
        /* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines ISRs */
    if (update == 1){
        update = 0;
        // char string[4];
        int rng_max = 920;
        int rng_min = 700;

        x = 100-(((sens.x-rng_min)*100)/(rng_max+70-rng_min));
        itoa(x, string, 10);
        oled_charMode(NORMALSIZE);
        oled_gotoxy(1, 1);
        oled_puts("Soil moisture");
        oled_gotoxy(1,2);
        oled_puts("---------------------");
        oled_gotoxy(1,4);
        oled_charMode(DOUBLESIZE);
        oled_puts(string);
        oled_gotoxy(5, 4);
        oled_puts("% ");
               
        itoa(dht12.temp_int, string, 10);
        oled_charMode(NORMALSIZE);
        oled_gotoxy(1, 7);
        oled_puts("Room temp:");
        oled_gotoxy(13, 7);
        oled_puts(string);
        oled_gotoxy(15, 7);
        oled_puts(" °C");
        oled_display();

        DDRB |= (1<<DDB0);
        if(x >= 50){
            PORTB |= (1<<PORTB0);
        }
        else{
            PORTB &= ~(1<<PORTB0);
        }
    }
}
    

    // Will never reach this
    return 0;
}

/* Interrupt service routines ----------------------------------------*/
/**********************************************************************
 * Function: Timer/Counter1 overflow interrupt
 * Purpose:  Transmit UART data four times per second.
 **********************************************************************/
ISR(TIMER1_OVF_vect)
{   static uint16_t no_of_overflows = 0;

    no_of_overflows++;
    if (no_of_overflows >= 1) {
    // Start ADC conversion
    ADCSRA = ADCSRA | (1<<ADSC);
    uint8_t value;
    char string[8];
    no_of_overflows = 0;
    }  // String for converted numbers by itoa()
}
ISR(TIMER0_OVF_vect){
    static uint16_t no_of_overflows = 0;

    no_of_overflows++;
    if (no_of_overflows >= 240 || update == 1) {  // do not read via TWI if oled is getting update
        
        twi_start();
        if (twi_write((SENSOR_ADR<<1) | TWI_WRITE) == 0) {
            // Set internal memory location
            twi_write(SENSOR_TEMP_MEM);
            twi_stop();
            // Read data from internal memory
            twi_start();
            twi_write((SENSOR_ADR<<1) | TWI_READ);
            dht12.temp_int = twi_read(TWI_ACK);
            dht12.temp_dec = twi_read(TWI_NACK);
        }
        twi_stop();
        // Do this every 6 x 16 ms = 100 ms
        no_of_overflows = 0;
        char string[4];
    
        int rng_max = 920;
        int rng_min = 700;

        int x = 100-(((sens.x-rng_min)*100)/(rng_max+70-rng_min));
        itoa(x, string, 10);

        uart_puts(string);
        uart_puts(" ");

        itoa(dht12.temp_int, string, 10);

        uart_puts(string);
        uart_puts(" ");
        update = 1;
    }
}

ISR(ADC_vect)
{
    uint16_t value;
    char string[4];  // String for converted numbers by itoa()

    // Read converted value
    // Note that, register pair ADCH and ADCL can be read as a 16-bit value ADC
    value = ADC;
    // Convert "value" to "string" and display it

    sens.x = (value); //prespat na realnou hodnotu
    update = 1;
}