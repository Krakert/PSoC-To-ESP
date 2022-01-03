/*
 * Author:      Stefan de Kraker
 * Version:     1.0
 *
 * Assignment 5, KITT 
 * Led bar, fade from left to right and back.
 * The delay between the next led is determined by the ADC reading.
 * This reading is mapped to defined delays.
 * 
 * It is important to add the following line to the `platformio.ini` file:
 * 
 * monitor_speed = 115200
 * 
 * This will set the baud rate to 115200 for the serial port.
 * Also this is the default baud rate of the ESP32
*/

/* Needed to control GPIO */
#include "driver/gpio.h"
/* Needed for ADC readings */
#include "driver/adc.h"
/* Include FreeRTOS for delay */
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>

/* the number of LEDs in the bar graph */
const uint8_t ledCount = 10; 
/* An array of pin numbers to which LEDs are attached */
int ledPins[] = {2, 4, 16, 17, 5, 18, 19, 21, 22, 23}; 

const uint8_t  ADC_MIN = 0;     // No need to change these two
const uint16_t ADC_MAX = 4095;  // 4095 under Single Read mode 

/* Define the delays */
#define DELAY_MIN       10
#define DELAY_MAX       500

/* 
 * This function will re-maps a number from one range to another. 
 * Source: https://www.arduino.cc/reference/en/language/functions/math/map/
 * 
 * So the ADC Ranges from 0-4095, and the delay between 10-500
 * This can be edited above, `DELAY_MIN` and `DELAY_MAX`.
 */
int map(int x, int in_min, int in_max, int out_min, int out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void app_main() {
    /* Initialize all the LEDS */
    for (uint8_t i = 0; i < ledCount; i++) {
        gpio_set_direction(ledPins[i], GPIO_MODE_OUTPUT);
        gpio_set_level(ledPins[i], 0);
    } 

    /* 
     * Set the attention level of the ADC channel, 11 is needed 
     * See: https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/adc.html#adc-attenuation 
     * 
     * ADC1_CHANNEL_6 == GPIO34
     */ 
    adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11);
    
    /* Main loop */
    while (1) {
        /* Loop over the LED array: */
        for (uint8_t i = 0; i < ledCount; i++) {
            if (i == 0){
                gpio_set_level(ledPins[i], 1);
            } else {
                gpio_set_level(ledPins[i - 1], 0);
                gpio_set_level(ledPins[i], 1);
            }
            /* Get a reading and map that to a delay time */
            vTaskDelay(map(adc1_get_raw(ADC1_CHANNEL_6), ADC_MIN, ADC_MAX, DELAY_MIN, DELAY_MAX) / portTICK_RATE_MS);
        }
        for (uint8_t i = ledCount - 2; i > 0; i--) {
            gpio_set_level(ledPins[i + 1], 0);
            gpio_set_level(ledPins[i], 1);
            /* Get a reading and map that to a delay time */
            vTaskDelay(map(adc1_get_raw(ADC1_CHANNEL_6), ADC_MIN, ADC_MAX, DELAY_MIN, DELAY_MAX) / portTICK_RATE_MS);
        }
       gpio_set_level(ledPins[1], 0); 
    }
}
