# Day 5 (4/11/2025)

## Goal

- use UART interrupt
- Interrupt Service Routine (ISR)
  - HAL_UART_RxCpItCallback();
- read input from terminal
- combine received character into string

- Baud rate: 115200 bits/s

## MINICOM

ls /dev/tty* | grep usb

minicom --device /dev/tty.usbmodem1102 -b 115200