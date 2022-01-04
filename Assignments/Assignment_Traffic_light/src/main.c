/*
 * Author:      Stefan de Kraker
 * Version:     1.0
 *
 * Assignment 3, Traffic light
 * Recreate a simple traffic light, that is by default red.
 * When the button is pressed, the light switches to green,
 * after a few seconds is turns orange, and then back to red.
*/

/* Needed to control GPIO */
#include "driver/gpio.h"
/* Include FreeRTOS for delay */
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>

/* Define the delays between the lights */
#define TIME_TO_GREEN       1500
#define TIME_TO_ORANGE      5000
#define TIME_TO_RED         2000

/* Define all the I/O needed */
const uint8_t pinsLeds[] = {18, 19, 21};
const uint8_t button = 33;

/* Boolean to check if the button is pressed */
uint8_t buttonPressed = 0;

void app_main() {
    /* Setup the LEDS, default state is off */
    for (uint8_t i = 0; i < 3; i++) {
        gpio_set_direction(pinsLeds[i], GPIO_MODE_OUTPUT);
        gpio_set_level(pinsLeds[i], 0);
    }
    /* Setup the button with a internal pull-down */
    gpio_set_direction(button, GPIO_MODE_INPUT);
    gpio_pulldown_en(button);

    /* Turn on the red by default */
    gpio_set_level(pinsLeds[0], 1);

    /* Main loop */
    while (1) {
        /* When the button is pressed, set the boolean to true (1) */
        if(gpio_get_level(button)){
            buttonPressed = 1;
        /* When the button is not pressed */
        } else {
            /* And the boolean is true (1) */
            if(buttonPressed){
                /* Cycle through the lights one by one */
                printf("Button was pressed\r\nWaiting for light to get green\r\n");
                vTaskDelay(TIME_TO_GREEN/ portTICK_RATE_MS);
                gpio_set_level(pinsLeds[0], 0);
                gpio_set_level(pinsLeds[2], 1);
                printf("Light is green\r\n");
                vTaskDelay(TIME_TO_ORANGE/ portTICK_RATE_MS);
                gpio_set_level(pinsLeds[2], 0);
                gpio_set_level(pinsLeds[1], 1);
                printf("Light is orange\r\n");
                vTaskDelay(TIME_TO_RED/ portTICK_RATE_MS);
                gpio_set_level(pinsLeds[1], 0);
                gpio_set_level(pinsLeds[0], 1);
                printf("Back to red\r\n");
                /* Set boolean back to false (0) */
                buttonPressed = 0;
            }
        }
        vTaskDelay(10 / portTICK_RATE_MS);
    }
}