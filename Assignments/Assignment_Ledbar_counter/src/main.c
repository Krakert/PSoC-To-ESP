/*
 * Author:      Stefan de Kraker
 * Version:     1.1
 *
 * Assignment 2a, Ledbar counter
 * This assignment display a number on the Ledbar.
 * Display the number 0: (all digits are zero (off))
 * ---------------------
 * | | | | | | | | | | |
 * ---------------------
 * Display the number 1: (turn on the most left LED (1))
 * ---------------------
 * | | | | | | | | | |X|
 * ---------------------
 * Display the number 5: (turn LED 5 on)
 * ---------------------
 * | | | | | |X| | | | |
 * ---------------------
 * This is done until 10, then go back to 0, with 1 sec interval
*/

/* Needed to control GPIO */
#include "driver/gpio.h"
/* Include FreeRTOS for delay */
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>

/* the number of LEDs in the bar graph */
const uint8_t ledCount = 10; 
/* An array of pin numbers to which LEDs are attached */
int ledPins[] = {2, 4, 16, 17, 5, 18, 19, 21, 22, 23}; 
/* OPTIONAL: get the length of the array, so that we can turn of the last LED */
uint8_t len = sizeof(ledPins)/sizeof(ledPins[0]);

void app_main() {
    /* Initialize all the LEDS */
    for (uint8_t i = 0; i < ledCount; i++) {
        gpio_set_direction(ledPins[i], GPIO_MODE_OUTPUT);
        gpio_set_level(ledPins[i], 0);
    }   

    /* Main loop */
    while (1) {
        /* Loop over the LED array: */
        for (uint8_t j = 0; j < ledCount + 1; j++) {
            /* Print out the index */
            printf("Counter is: %i\r\n", j);
            /* LEDS only go on when counter is higher then 0 */
            if (j != 0) {
                /* Turn of the first LED, needs own if, otherwise negative index in array */
                if (j > 1){
                    gpio_set_level(ledPins[j - 2], 0);
                }
                gpio_set_level(ledPins[j - 1], 1);
            }
            /* Small delay */
            vTaskDelay(500 / portTICK_RATE_MS);
        }
        /* Turn of the last LED (len - 1 == 9) */
        gpio_set_level(ledPins[len - 1], 0);
    }
}
