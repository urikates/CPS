#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED1 35
#define LED2 33
#define LED3 26
#define BT 14

void app_main() {
    gpio_set_direction(LED1, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED2, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED3, GPIO_MODE_OUTPUT);
    gpio_set_direction(BT, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BT, GPIO_PULLDOWN_ONLY);

    int leds =0;

    while (1){
        int sbt =gpio_get_level(BT);

        if(sbt == 1){
            if(leds == 0){
                leds=1;
                vTaskDelay(200/portTICK_RATE_MS);
                gpio_set_level(LED1, 1);
                vTaskDelay(300/portTICK_RATE_MS);
                gpio_set_level(LED2, 1);
                vTaskDelay(250/portTICK_RATE_MS);
                gpio_set_level(LED3, 1);
            } else{
                leds=0;
                vTaskDelay(200/portTICK_RATE_MS);
                gpio_set_level(LED1, 0);
                vTaskDelay(300/portTICK_RATE_MS);
                gpio_set_level(LED2, 0);
                vTaskDelay(250/portTICK_RATE_MS);
                gpio_set_level(LED3, 0);
            }
        }

    }
}