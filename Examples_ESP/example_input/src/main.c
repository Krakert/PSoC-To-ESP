/*
 * Author:      Stefan de Kraker
 * Version:     1.0
 *
 * Simple example to show the use of a GPIO Input
 * When a GPIO pin is high, in this example pin 15, print "Hell world"
*/

/* Needed to control GPIO */
#include "driver/gpio.h"
/* Include FreeRTOS for delay */
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
/* Serial communication is done by standard stdio */
#include <stdio.h>

/* The GPIO Pin to read */
#define BUTTON_GPIO 15

void app_main() {
    /* Do your setup here */
    /* Setup BLINK_GPIO as a output pin */
    gpio_set_direction(BUTTON_GPIO, GPIO_MODE_INPUT);

    /* 
    * Enable internal pull down on the GPIO PIN 
    * This step can be skipped and a external pull up/down resistor can be used
    */
    gpio_pulldown_en(BUTTON_GPIO);

    /* Main loop */
    while (1) {
        /* Get the GPIO GPIO input level */
        if (gpio_get_level(BUTTON_GPIO)){
            printf("Hello world\r\n");
        }
    vTaskDelay(100 / portTICK_RATE_MS);
    }
}