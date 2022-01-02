/* UART Echo Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "string.h"

/* Define the UART interface */
#define UART_PORT_NUM       UART_NUM_1
#define UART_PIN_TX         1
#define UART_PIN_RX         3
#define UART_BAUD_RATE      115200
#define BUF_SIZE            1024


void app_main(void) {

    uart_set_pin(UART_PORT_NUM, UART_PIN_TX, UART_PIN_RX, -1, -1);
    uart_driver_install(UART_PORT_NUM, BUF_SIZE , BUF_SIZE, 0, NULL, 0);    

    uart_write_bytes(UART_PORT_NUM, "STARTED\n\r", strlen("STARTED\n\r"));

    char line[BUF_SIZE];

    /* Configure a temporary buffer for the incoming data */
    uint8_t *data = (uint8_t *) malloc(BUF_SIZE);

    while (1) {
        // Read data from the UART
        int len = uart_read_bytes(UART_PORT_NUM, data, BUF_SIZE, 20 / portTICK_RATE_MS);
        // Write data back to the UART
        snprintf(line, len+10, "ECHO IS: %s\r\n\n", data);

        if(len > 0)
            uart_write_bytes(UART_PORT_NUM, (const char *) line, strlen(line));
        
        vTaskDelay(10 / portTICK_RATE_MS);
    } 
}
