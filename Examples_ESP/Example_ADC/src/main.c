/*
 * Author:      Stefan de Kraker
 * Version:     1.0
 *
 * ADC example, read from the ADC port and re-map the values.
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

const uint8_t  ADC_MIN = 0;     // No need to change these two
const uint16_t ADC_MAX = 4095;  // 4095 under Single Read mode 

/* Define the new min and max of the range */
#define NEW_MIN       10
#define NEW_MAX       500

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
    /* 
     * Set the attention level of the ADC channel, 11 is needed 
     * See: https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/adc.html#adc-attenuation 
     * 
     * ADC1_CHANNEL_6 == GPIO34
     */ 
    adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11);
    
    /* Main loop */
    while (1) {
        /* Get the Raw ADC value */
        int rawData = adc1_get_raw(ADC1_CHANNEL_6);
        /* print this out, with the remapped value */
        printf("ADC reading, RAW data: %5i, after re-mapping: %5i\n",rawData , map(rawData, ADC_MIN, ADC_MAX, NEW_MIN, NEW_MAX));
        /* Do this every 500 ms */
        vTaskDelay(500 / portTICK_RATE_MS);
    }
}
