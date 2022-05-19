#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED 26
#define BT 14

void app_main() {
    gpio_set_direction(LED, GPIO_MODE_OUTPUT);
    gpio_set_direction(BT, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BT, GPIO_PULLDOWN_ONLY);

    int led_state=0;

    while(1){
        int state_bt = gpio_get_level(BT);
        printf("Estado del botón: %i \n", state_bt);

        if(state_bt==1){
            if(led_state==0){
                led_state=1;
                gpio_set_level(LED,1);
            }else{
                led_state=0;
                gpio_set_level(LED,0);
            }
        }
        printf("Estado del LED: %i \n", led_state);
        vTaskDelay(200/portTICK_RATE_MS);
    }
   

}