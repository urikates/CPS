#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED 26
#define BT 14

int leds;

void onoff(void *pvParameter){
    while(1){
        int bts = gpio_get_level(BT);
        if(bts==1){
            if(leds==0){
                gpio_set_level(LED, 1);
                leds=1;
            }
            if(leds==1){
                gpio_set_level(LED, 0);
                leds=0;
            }
        }
    }
}

void app_main() {
    gpio_set_direction(LED, GPIO_MODE_OUTPUT);
    gpio_set_direction(BT, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BT, GPIO_PULLDOWN_ONLY);
    

    xTaskCreate(onoff, "onoff", 1000, NULL, 1, NULL);

}