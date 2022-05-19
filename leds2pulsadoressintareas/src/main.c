#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED1 35
#define LED2 33
#define LED3 26
#define BT1 14
#define BT2 12

void app_main() {
    gpio_set_direction(LED1, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED2, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED3, GPIO_MODE_OUTPUT);
    gpio_set_direction(BT1, GPIO_MODE_INPUT);
    gpio_set_direction(BT2, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BT1, GPIO_PULLDOWN_ONLY);
    gpio_set_pull_mode(BT2, GPIO_PULLDOWN_ONLY);

    while(1){
        int sbt1 = gpio_get_level(BT1);
        int sbt2 = gpio_get_level(BT2);

        printf("Estado del boton 14: %i \n", sbt1);
        printf("Estado del boton 12: %i \n", sbt2);
        
        if(sbt1==1){
            vTaskDelay(200/portTICK_RATE_MS);
            gpio_set_level(LED1, 1);
            vTaskDelay(300/portTICK_RATE_MS);
            gpio_set_level(LED2,1);
            vTaskDelay(250/portTICK_RATE_MS);
            gpio_set_level(LED3, 1);
        }
        if(sbt2==1){
            vTaskDelay(200/portTICK_RATE_MS);
            gpio_set_level(LED1, 0);
            vTaskDelay(300/portTICK_RATE_MS);
            gpio_set_level(LED2, 0);
            vTaskDelay(250/portTICK_RATE_MS);
            gpio_set_level(LED3, 0);
        }

        vTaskDelay(200/portTICK_RATE_MS);

    }
}