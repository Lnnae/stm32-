/*
FreeRTOS low power demo.
*/
#include "FreeRTOS.h"
#include "task.h"
#include "exti.h"
#include "led.h"
#include "key.h"
#include "usart.h"
#include "stm32f10x_pwr.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include <stdio.h>
#include <stdint.h>

void start_task(void *pvParameters);
void lowpower_task(void *pvParameters);
static void enter_low_power(void);

#define START_TASK_STACK_SIZE 128
#define START_TASK_PRIO 1
TaskHandle_t start_task_handler;

#define LOWPOWER_TASK_STACK_SIZE 128
#define LOWPOWER_TASK_PRIO 2
TaskHandle_t lowpower_task_handler;

void freertos_demo(void)
{
    BaseType_t xReturn = pdPASS;
    xReturn = xTaskCreate((TaskFunction_t)start_task,
                          "start_task",
                          (configSTACK_DEPTH_TYPE)START_TASK_STACK_SIZE,
                          NULL,
                          (UBaseType_t)START_TASK_PRIO,
                          &start_task_handler);
    if (xReturn == pdPASS)
    {
        printf("start_task created\r\n");
        vTaskStartScheduler();
    }
    else
    {
        printf("start_task create failed\r\n");
    }
}

void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();

    xTaskCreate((TaskFunction_t)lowpower_task,
                "lowpower_task",
                (configSTACK_DEPTH_TYPE)LOWPOWER_TASK_STACK_SIZE,
                NULL,
                (UBaseType_t)LOWPOWER_TASK_PRIO,
                &lowpower_task_handler);

    vTaskDelete(NULL);
    taskEXIT_CRITICAL();
}

void lowpower_task(void *pvParameters)
{
    uint8_t key = 0;
    uint32_t idle_seconds = 0;

    while (1)
    {
        key = KEY_Scan(0);
        if (key == KEY0_PRES)
        {
            idle_seconds = 0;
            printf("KEY0\r\n");
            vTaskDelay(pdMS_TO_TICKS(20));
        }
        else if (key == KEY1_PRES)
        {
            idle_seconds = 0;
            printf("KEY1\r\n");
            vTaskDelay(pdMS_TO_TICKS(20));
        }
        else
        {
            vTaskDelay(pdMS_TO_TICKS(1000));
            idle_seconds++;
            printf("Idle Time: %lu s\r\n", (unsigned long)idle_seconds);
        }

        if (idle_seconds >= 5)
        {
            printf("Entering Low Power Mode...\r\n");
            vTaskDelay(pdMS_TO_TICKS(10));
            enter_low_power();
            idle_seconds = 0;
            printf("Woke up from Low Power!\r\n");
        }
    }
}

static void enter_low_power(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

    LED1 = 0;
    LED0 = 0;

    USART_Cmd(USART1, DISABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, DISABLE);

    PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);
    //__WFI();
    SystemInit();
    uart_init(115200);
    LED_Init();
    KEY_Init();
    KEY0_EXTI_Init();
    KEY1_EXTI_Init();
}
