// Serial communication
#include <stdio.h>
// Include FreeRTOS for delay 
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

void app_main(){
    // Do your setup here
    // Init of a simple uint8_t
    uint8_t count = 0;

    // Main loop    
    while(1){
        printf("Hello world!\n"); 
        count = count + 1;
        printf("count now is: %i \r\n", count);
        // added small delay of 0.5 seconds
        vTaskDelay(500 / portTICK_RATE_MS);
    } 
}