#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED 2
#define BT1 17


void app_main() {
    gpio_set_direction(LED, GPIO_MODE_OUTPUT);
    gpio_set_direction(BT1, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BT1, GPIO_PULLDOWN_ONLY);

   while(1){
        int state_bt1 =gpio_get_level(BT1);
        if(state_bt1==1){
            gpio_set_level(LED,1);
        }else{
            gpio_set_level(LED,0);
        }
        vTaskDelay(200/portTICK_RATE_MS);
    }
}