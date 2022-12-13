#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "freertos/semphr.h"
#define BLINK_GPIO 2

#define  ESP_INTR_FLAG_DEFAULT 0
//#define BLINK_LED 13
#define GPIO_INPUT_IO_0 27
int buttonCount = 0;
int i = 0;
TaskHandle_t printVariableTask = NULL;

void most_priority(void* pvParameter) {
   
    while(1){
         printf("111111111111111111111111111111111111\n");
        vTaskDelay(3000 / portTICK_RATE_MS);
    }
}

void hello_task(void *pvParameter)
{
	while(1)
	{
	    printf("Hello world!\n");
	    vTaskDelay(500 / portTICK_RATE_MS);
	}
}
void blinky(void *pvParameter)
{
    gpio_pad_select_gpio(BLINK_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
    while(1) {
        /* Blink off (output low) */
        printf("BLINKYYYYYYY!\n");
        gpio_set_level(BLINK_GPIO, 0);
        vTaskDelay(1000 / portTICK_RATE_MS);
        /* Blink on (output high) */
        gpio_set_level(BLINK_GPIO, 1);
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}
void app_main()
{   
    xTaskCreate(&most_priority, "most_priority", 2048, NULL, 5, NULL);
    xTaskCreate(&hello_task, "hello_task", 2048, NULL, 4, NULL);
    xTaskCreate(&blinky, "blinky", 2048,NULL,3,NULL );
}
