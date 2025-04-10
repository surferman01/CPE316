# Day 4 (4/9/2025)

## TODOs

- solder LCD module by next week
  - see soldering video on canvas under labs/homework, videos
- Lab 1 due monday 4/14

## Lab 1 Overview

- make lights flash on board
- SOS morse code
- HAL_Delay(time) to flash different patters
  - this is blocking code
  - this is no good because it will prevent our button presses from registering
- for every thread, have a switch detector

## Universal Asynchronous Receive and Transmit (UART)

- recommended standard (RS232)

- RX = USART 2 -> PA3
- TX = USART 2 -> PA2

## Transfer

Serial
- better for long distance and noise immunity

Parallel


DTE
- Data Terminal Equipment

DCE
- Data Communication Equipment

## Software Implementing

https://www.disca.upv.es/aperles/arm_cortex_m3/llibre/st/STM32L486xx_User_Manual/stm32l4xx__hal__uart_8c.html

HAL_UART_Transmit

void UART_send(UART_HandleTypeDef *huart, char buffer[]) {
    // buffer address or pointer
    HAL_UART_Transmit(huart, (uint8_t*) buffer, strlen(buffer), HAL_MAX_DELAY)
}