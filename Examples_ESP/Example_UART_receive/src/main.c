/*
 * Author:      Stefan de Kraker
 * Version:     1.0
 *
 * Simple example of the use of UART
 * It is important to add the following lines to the `platformio.ini` file:
 * 
 * monitor_speed = 115200
 * monitor_flags = 
 *     --echo 
 *     --filter
 *     send_on_enter
 *     --eol
 *     CRLF
 * 
 * This will set the baud rate to 115200 for the serial port,
 * and make is possible to send messages to the ESP32.
*/
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
    /* Define the UART port, and the GPIO needed for it */
    uart_set_pin(UART_PORT_NUM, UART_PIN_TX, UART_PIN_RX, -1, -1);
    /* Setup the driver, by defining buffers and if needed interrupts */
    uart_driver_install(UART_PORT_NUM, BUF_SIZE , BUF_SIZE, 0, NULL, 0);    
    /* Write data to the UART port */ 
    uart_write_bytes(UART_PORT_NUM, "STARTED\n\r", strlen("STARTED\n\r"));

    /* Configure a buffer for the incoming data */
    char data[BUF_SIZE];
    /*Configure a buffer for the string output */
    char line[BUF_SIZE];

    while (1) {
        /* Read data from the UART */
        int len = uart_read_bytes(UART_PORT_NUM, data, BUF_SIZE, 20 / portTICK_RATE_MS);
        /* Place data in a buffer */
        snprintf(line, len + 10 ,"ECHO IS: %s\r\n\n", data);
        /* If ther is data, write that back to the COM port */
        if(len > 0) {
            uart_write_bytes(UART_PORT_NUM, (const char *) line, strlen(line));
        }
    } 
}
