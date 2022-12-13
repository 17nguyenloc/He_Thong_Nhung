#include <stdio.h> 
 #include "freertos/FreeRTOS.h" 
 #include "freertos/task.h" 
 #include "freertos/timers.h" 
 #include "esp_system.h" 
 #include "driver/gpio.h" 
 #include <inttypes.h> 
 #include <stdio.h> 
 #include "sys/time.h" 
 #define Timer1 10 
 #define Timer2 5 
  
 #define TIMER_1_PERIOD 2000 
 #define TIMER_2_PERIOD 3000 
  
 TimerHandle_t timer1; 
 TimerHandle_t timer2; 
  
 BaseType_t xTimer1Started; 
 BaseType_t xTimer2Started; 
  
 uint8_t timer1_counter = 0; 
 uint8_t timer2_counter = 0; 
  
 struct timeval tv_now; 
 static inline void printTime() ;
 static void vTimerCallback(TimerHandle_t tim) ;
void app_main(void) 
 { 
     timer1_counter = 0; 
     timer1 = xTimerCreate( 
         "Timer 1", 
         pdMS_TO_TICKS(TIMER_1_PERIOD), 
         pdTRUE, // Auto reload 
         1, 
         vTimerCallback); 
  
     timer2_counter = 0; 
     timer2 = xTimerCreate( 
         "Timer 2", 
         pdMS_TO_TICKS(TIMER_2_PERIOD), 
         pdTRUE, // Auto reload 
         2, 
         vTimerCallback); 
  
     if ((timer1 != NULL) && (timer2 != NULL)) //timer = null thi khong the khoi tao
                                                // timer != null thi khoi tao thanh cong, 
     { 
         xTimer1Started = xTimerStart(timer1, 0); 
         xTimer2Started = xTimerStart(timer2, 0); 
     } 
 }
 static inline void printTime() 
 { 
     gettimeofday(&tv_now, NULL); 
     printf("\t second = %ld \n", tv_now.tv_sec); 
 } 
  
 static void vTimerCallback(TimerHandle_t tim) 
 { 
     uint32_t id = (uint32_t) pvTimerGetTimerID(tim); 
  
     if (id == 1) 
     { 
         timer1_counter++; 
         printf("%s \t -- \t %d ", "ahihi" , timer1_counter); 
         printTime(); 
         if (timer1_counter == Timer1) 
         { 
             if (xTimerStop(tim, 0) == pdFAIL) 
             { 
                 printf("Timer 1 cannot stop\n"); 
             } 
         } 
     } 
     else if (id == 2) 
     { 
         timer2_counter++; 
         printf("%s\t -- \t %d", "ihaha", timer2_counter); 
        printTime(); 
         if (timer2_counter == Timer2) 
         { 
             if (xTimerStop(tim, 0) == pdFAIL) 
             { 
                 printf("Timer 2 cannot stop\n"); 
             } 
         } 
     } 
     else 
     { 
         printf("Error: Invalid ID %d\n", id); 
     } 
 } 
  
