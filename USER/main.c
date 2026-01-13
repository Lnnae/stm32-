#include "stm32f10x.h"

#include "sys.h" 
#include "delay.h" 
#include "usart.h" 
#include "led.h" 
#include "exti.h" 
#include "timer.h"
#include "key.h"
#include "FreeRTOS.h" 
#include "task.h" 
#include "freertos_demo.h" 


int main(void) 
{ 
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//����ϵͳ�ж����ȼ�����4   
	 delay_init();          //��ʱ������ʼ��    
	 uart_init(115200);      //��ʼ������ 
	 LED_Init();         //��ʼ��LED 
	 KEY_Init(); 
	 KEY1_EXTI_Init();
//	 TIM3_Int_Init(10000 - 1,9000 - 1);
//	 TIM4_Int_Init(10000 - 1,9000 - 1);
	printf("System Initialized. Starting RTOS...\r\n");
//	 EXTIX_Init();
	 freertos_demo();
 while(1)
 {
		
 
 }
	 
	 
}
// //������
// void start_task(void *pvParameters) 
// { 
//     taskENTER_CRITICAL();           //�����ٽ��� 
//     //����LED0���� 
//     xTaskCreate((TaskFunction_t  )led0_task,       
//                 (const char*     )"led0_task",     
//                 (uint16_t        )LED0_STK_SIZE,  
//                 (void*           )NULL,     
//                 (UBaseType_t     )LED0_TASK_PRIO,  
//                 (TaskHandle_t*   )&LED0Task_Handler);    
//     //����LED1���� 
//     xTaskCreate((TaskFunction_t  )led1_task,      
//                 (const char*     )"led1_task",    
//                 (uint16_t       )LED1_STK_SIZE,  
//                 (void*           )NULL, 
//                 (UBaseType_t     )LED1_TASK_PRIO, 
//                 (TaskHandle_t*   )&LED1Task_Handler);         
//     vTaskDelete(StartTask_Handler);   //ɾ����ʼ���� 
//     taskEXIT_CRITICAL();            //�˳��ٽ��� 
// } 
 
// //LED0������  
// void led0_task(void *pvParameters) 
// { 
//     while(1) 
//     { 
//         LED0=~LED0; 
//         vTaskDelay(500); 
//     } 
// }    
 
// //LED1������ 
// void led1_task(void *pvParameters) 
// { 
//     while(1) 
//     { 
//         LED1=0; 
//         vTaskDelay(200); 
//         LED1=1; 
//         vTaskDelay(800); 
//     } 
// }
