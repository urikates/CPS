#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"


#define LED 2 //Define el puerto que vamos a utilizar 
#define BT1 17
#define BT2 22



    
void app_main() {
    //PARA SETEAR DIRECCIONES Y MODOS DE PULL, DEBEN IR DENTRO DEL MAIN 
    gpio_set_direction(LED,GPIO_MODE_OUTPUT); //PARA DEFINIR EL MODO SALIDA O ENTRADA 
    gpio_set_direction(BT1,GPIO_MODE_INPUT);
    gpio_set_direction(BT2,GPIO_MODE_INPUT);
    gpio_set_pull_mode(BT1,GPIO_PULLDOWN_ONLY);
    gpio_set_pull_mode(BT2,GPIO_PULLDOWN_ONLY);
    int state_led=0;
    printf(state_led+"\n");
        
    while(1){
        int state_bt1 = gpio_get_level(BT1);
        printf("Estado del Boton 17: %i \n",state_bt1);
        int state_bt2 = gpio_get_level(BT2);
        printf("Estado del boton 22: %i \n",state_bt2);
        if(state_bt1==1){
            gpio_set_level(LED,1);
            printf("LED On\n");  
        }
        if (state_bt2==1){
           gpio_set_level(LED,0);
           printf("LED Off\n");
        }
        vTaskDelay(200/portTICK_RATE_MS);
        }
        
    }
    
    //vTaskDelay(1000 / portTICK_RATE_MS); Tarea de retardo, el argumento indca 1000 ms, es decir 1 segundo