/*
 * Author:      Stefan de Kraker
 * Version:     1.0
 *
 * Simple example to show the use of a GPIO Output
*/

/* Needed to control GPIO */
#include "driver/gpio.h"
/* Include FreeRTOS for delay */
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

/* 
 * Built-in LED on the ESP32 DEVKIT C1 is on pin 2
 * pinout https://www.mischianti.org/wp-content/uploads/2020/11/ESP32-DOIT-DEV-KIT-v1-pinout-mischianti.png
 * TTGo-koala does not have built-in LED, just use a external LED instead
 * Pinout: https://ae01.alicdn.com/kf/HTB1OhKrbyYrK1Rjy0Fdq6ACvVXas.jpg 
*/
#define BLINK_GPIO 2

void app_main() {
    /* Do your setup here */
    /* Setup BLINK_GPIO as a output pin */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

    /* Main loop */
    while (1) {
        /* set GPIO high */
        gpio_set_level(BLINK_GPIO, 1);
        /* delay of 750 ms */
        vTaskDelay(750 / portTICK_RATE_MS);
        /* set GPIO low */
        gpio_set_level(BLINK_GPIO, 0);
        /* delay of 750 ms */
        vTaskDelay(750 / portTICK_RATE_MS);
    }
}