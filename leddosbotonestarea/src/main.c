#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED 26
#define BT1 14
#define BT2 12

void encender(void *pvParameter){
    while(1){
        int bts1 = gpio_get_level(BT1);
        if(bts1==1){
            gpio_set_level(LED,1);
        } 
    }
}

void apagar(void *pvParameter){
    while(1){
        int bts2 = gpio_get_level(BT2);
        if(bts2==1){
            gpio_set_level(LED,0);
        }
    }
}
void app_main() {
    gpio_set_direction(LED, GPIO_MODE_OUTPUT);
    gpio_set_direction(BT1, GPIO_MODE_INPUT);
    gpio_set_direction(BT2, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BT1, GPIO_PULLDOWN_ONLY);
    gpio_set_pull_mode(BT2, GPIO_PULLDOWN_ONLY);

    xTaskCreate(encender, "encender", 1000, NULL, 1, NULL);
    xTaskCreate(apagar, "apagar", 1000, NULL, 1, NULL);

}