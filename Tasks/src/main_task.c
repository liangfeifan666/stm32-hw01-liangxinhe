/*
 * @Author: liangfeifan666 bolanglang0903@outlook.com
 * @Date: 2026-10-05 12:31:57
 * @LastEditors: liangfeifan666 bolanglang0903@outlook.com
 * @LastEditTime: 2026-10-05 19:17:40
 * @FilePath: \STM32F103MIN\Tasks\src\main_task.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "main_task.h"
#include "tim.h"
#include "iwdg.h"

#define HW_TASK  3

#if (HW_TASK < 1) || (HW_TASK > 3)
#error "HW_TASK 只能取 1 / 2 / 3"
#endif

#if HW_TASK >= 2
/* 全局 tick：定时器更新中断里自增，调试器监视它验证 1ms 周期 */
volatile uint32_t tick = 0;

/* 定时器更新中断，每 1ms 进来一次。全工程只此一份，统一放 Tasks */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM2) {
    tick++;
#if HW_TASK == 2
    HAL_IWDG_Refresh(&hiwdg);   /* 第 2 题：喂狗 → 芯片不复位 */
#endif
  }
}
#endif /* HW_TASK >= 2 */

/* 业务初始化：上电时在 main.c 的 USER CODE 2 里调用一次 */
void task_init(void)
{
  /* 第 1 题：PC13 推挽输出，低电平点亮板载 LED */
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

#if HW_TASK >= 2
  /* 第 2 / 3 题：启动 TIM2 更新中断，1ms 一次 */
  HAL_TIM_Base_Start_IT(&htim2);
#endif
}
