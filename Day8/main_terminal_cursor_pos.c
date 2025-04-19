#include "main.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

UART_HandleTypeDef huart2;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);

char *cursor_pos(int, int);

void UART_send(UART_HandleTypeDef *huart, char buffer[])
{
    HAL_UART_Transmit(huart, (uint8_t *)buffer, strlen(buffer), HAL_MAX_DELAY);
 }

void UART_send_newline(UART_HandleTypeDef *huart)
{
      HAL_UART_Transmit(huart, (uint8_t *)"\n\r", 2, HAL_MAX_DELAY);
}

int main(void)
{

	int Count = 0;
	char buffer[15];
	char *location;

    char ClearScreen[] = { 0x1B, '[', '2' , 'J',0 }; 	// Clear the screen
    char CursorHome[] = { 0x1B, '[' , 'H' , 0 }; 	// Home the cursor
    char Goto_5_5[] = { 0x1B, '[', '5', ';' ,'5', 'H', 0 }; //  Move cursor to specified position (5, 5)

  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART2_UART_Init();

  UART_send(&huart2, ClearScreen);	// clear screen with the phrase: ESC, [ 2 J NUL
  UART_send(&huart2, CursorHome);	// move cursor position home with the phrase: ESC, [, H, NUL

  while (1)
  {
     itoa(Count, buffer, 10);
     UART_send(&huart2, Goto_5_5 );
     //location = cursor_pos(20, 15);
     //UART_send(&huart2, location);
	 UART_send(&huart2, buffer);
	 UART_send_newline(&huart2);
     Count++;
	 HAL_Delay(1000);
  }
}

char *cursor_pos(int row, int col)
{
    static char CurPos[10];

    sprintf(CurPos, "\x1B[%d;%dH", row, col);
    return CurPos;
}
