/*
 * Author:      Stefan de Kraker
 * Version:     1.0
 *
 * Assignment 2b, How much have you had already
 * This assignment display the number of drinks you have had.
 * By using the LED bar from assignment 2a (and some code). 
 * Pressing one button will increase the total amount,the other will decrease the amount.
*/

/* Needed to control GPIO */
#include "driver/gpio.h"
/* Include FreeRTOS for delay */
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>

 
/* An array of pin numbers to which LEDs are attached */
int ledPins[] = {2, 4, 16, 17, 5, 18, 19, 21, 22, 23}; 
/* An array of pin numbers to which the buttons are attached */
int buttonPins[] = {33, 32};
/* OPTIONAL: get the length of the arrays */
uint8_t lenLed = sizeof(ledPins)/sizeof(ledPins[0]);
uint8_t lenButton = sizeof(buttonPins)/sizeof(buttonPins[0]);

/* Counter of the amount of drinks you had so far */
uint8_t amountOfDrinks = 0;

/* Two bools for checking if the buttons are pressed */
uint8_t pressedButtonLower = 0;
uint8_t pressedButtonHigher = 0;

/* Here the last LED that was turned on in saved */
uint8_t lastLed = 0;

void updateLeds(uint8_t amountOfDrinks){
    if (amountOfDrinks != 0) {
        /* Turn off the LED that was turned on the last time */
        gpio_set_level(ledPins[lastLed], 0);
        /* Turn on the correct LED, offset -1 for array index*/
        gpio_set_level(ledPins[amountOfDrinks - 1], 1);
        /* Save the LED that is turned on */
        lastLed = (amountOfDrinks - 1);
    } else { 
        /* When 0, turn off all LEDS, just to be sure (OPTIONAL, just turn off LED 1)*/
        for (uint8_t i = 0; i < lenLed; i++) {
            gpio_set_level(ledPins[i], 0);
        }  
    }
}

void app_main() {
    /* Initialize all the LEDS */
    for (uint8_t i = 0; i < lenLed; i++) {
        gpio_set_direction(ledPins[i], GPIO_MODE_OUTPUT);
        gpio_set_level(ledPins[i], 0);
    }  
    /* Initialize all the buttons */
    for (uint8_t j = 0; j < lenButton; j++){
        gpio_set_direction(buttonPins[j], GPIO_MODE_INPUT);
        gpio_pulldown_en(buttonPins[j]);
    } 

    /* Main loop */
    while (1) {
        /* Check if the button is pressed */
        if (gpio_get_level(buttonPins[0])){
            pressedButtonHigher = true;
        /* Check if the button is released */
        } else {
            if (pressedButtonHigher){
                 /* Check if not 10 */
                if (amountOfDrinks != 10){
                    /* Increase the amount */
                    amountOfDrinks++;
                    /* Update the led bar */
                    updateLeds(amountOfDrinks);
                    printf("One drink more, total is: %i\r\n", (amountOfDrinks));
                /* Can't go above 10 */
                } else {
                    printf("You had enough drinks\r\n");
                }
                /*lower flag */
                pressedButtonHigher = false;
            }
        } 
        /* Check if the other button is pressed */
        if (gpio_get_level(buttonPins[1])){
            pressedButtonLower = true;
        /* Check if the other button is released */
        } else {
            /* Only do something if flag is set */
            if (pressedButtonLower){
                /* Check if not 0 */
                if (amountOfDrinks != 0){
                    /* Reduce the amount */
                    amountOfDrinks--;
                    /* Update the led bar */
                    updateLeds(amountOfDrinks);
                    /* Print the total amount */
                    printf("One drink less, total is: %i\r\n", (amountOfDrinks));
                /* Can't go below 0 */
                } else {
                    printf("Can't drink less then 0 drinks\r\n");
                }
                /*lower flag */
                pressedButtonLower = false;
            }
        }
        /* Small delay */
        vTaskDelay(50 / portTICK_RATE_MS);
    }
}
