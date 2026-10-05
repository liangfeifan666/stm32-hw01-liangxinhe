# stm32-hw01-liangxinhe
HelloWorld 战队电控组 2026 纳新第一次作业 梁昕禾 3250100274 | STM32F103C8T6：GPIO 点灯 / TIM2 1ms 中断计数 / IWDG 超时复位

## 三题切换
三题共用一份源码，改 Tasks/src/main_task.c 顶部的宏后重新编译：


| 1 | GPIO | PC13 低电平点亮板载 LED（不喂狗，约 2s 复位） |
| 2 | 定时器 | TIM2 1ms 中断，tick 每秒 +1000，回调喂狗 |
| 3 | 看门狗 | 去掉喂狗，tick 涨到约 2000 后复位归零，循环 |