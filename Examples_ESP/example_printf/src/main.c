/*
 * Author:      Stefan de Kraker
 * Version:     1.0
 *
 * Simple example of the use of printf
 * It is important to add the following line to the `platformio.ini` file:
 * 
 * monitor_speed = 115200
 * 
 * This will set the baud rate to 115200 for the serial port.
 * Also this is the default baud rate of the ESP32
*/

/* Needed to control GPIO */
#include "driver/gpio.h"
/* Include FreeRTOS for delay */
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
/* Serial communication is done by standard stdio */
#include <stdio.h>

void app_main(){
    /* Do your setup here */
    /* Init of a simple uint8_t */
    uint8_t count = 0;

    /* Main loop */    
    while(1){
        printf("Hello world!\n"); 
        count = count + 1;
        printf("count now is: %i \r\n", count);
        /* added small delay of 0.5 seconds */
        vTaskDelay(500 / portTICK_RATE_MS);
    } 
}