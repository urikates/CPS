#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"
#include "freertos/task.h"

#define LED 2 //Define el puerto que vamos a utilizar 
#define BT1 17
#define BT2 22



    
void app_main() {
    //PARA SETEAR DIRECCIONES Y MODOS DE PULL, DEBEN IR DENTRO DEL MAIN 
    gpio_set_direction(LED,GPIO_MODE_OUTPUT); //PARA DEFINIR EL MODO SALIDA O ENTRADA 
    gpio_set_direction(BT1,GPIO_MODE_INPUT);
    gpio_set_direction(BT2,GPIO_MODE_INPUT);
    gpio_pulldown_en(BT1);
    gpio_pulldown_en(BT2);

    int state_bt1 = gpio_get_level(BT1);
    int state_bt2 = gpio_get_level(BT2);
    while(1){
        if(state_bt1==1){
            gpio_set_level(LED,1);
            printf("LED On");
        }
        if(state_bt2==1){
            gpio_set_level(LED,0);
            printf("LED Off");
        }
        if(state_bt1==1 && state_bt2==1){
            gpio_set_level(LED,0);
        }
    }
    //vTaskDelay(1000 / portTICK_RATE_MS); Tarea de retardo, el argumento indca 1000 ms, es decir 1 segundo
}