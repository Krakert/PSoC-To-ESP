/*
 * Author:      Stefan de Kraker
 * Version:     1.1
 *
 * Assignment 1, heartbeat
 * This assignment teaches the use of the delay function,
 * and controlling an GPIO on and off.
*/

/* Needed to control GPIO */
#include "driver/gpio.h"
/* Include FreeRTOS for delay */
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

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
        /* delay of 100 ms */
        vTaskDelay(100 / portTICK_RATE_MS);
        /* set GPIO high */
        gpio_set_level(BLINK_GPIO, 1);
        /* delay of 350 ms */
        vTaskDelay(350 / portTICK_RATE_MS);
        /* set GPIO low */
        gpio_set_level(BLINK_GPIO, 0);
        /* delay of 50 ms */
        vTaskDelay(50 / portTICK_RATE_MS);
    }
}
