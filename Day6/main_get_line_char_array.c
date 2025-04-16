#include "main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NLINES 4	// Let it have 4 rows
#define MAXLINE 6	// Let each row have 5 char maximum with a null

#define UART_REC 0x01	// for flags use
#define Done 0x02		// for flags use
unsigned short flags;	// for flags use

UART_HandleTypeDef huart2;
char Buffer[1];			// for receiving and send single byte use

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);

// See C_programming example on page 203
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  flags |= UART_REC;
  HAL_UART_Receive_IT(&huart2, (uint8_t *)Buffer, 1);
}

// Get a line input and return how many chars in it
int get_line(char line[], int max)
{
	int i=0;	// Index record to save each char

	while (!(flags & Done))		// Once in this function, it'll get char till '\r'
	{
	  if (flags & UART_REC)		// Only work when UART interrupt detected
	  {
		 flags &= ~UART_REC;	// clear the flag
	     HAL_UART_Transmit(&huart2, (uint8_t *)Buffer, 1, HAL_MAX_DELAY);  // Echo back

		 if (Buffer[0] != '\r') // if note carriage return, save to array
		   line[i++] = Buffer[0];

		 else
		   flags |= Done;
	  }
	}

	line[i] = '\0'; 				// terminate with null
		return i;
}

int main(void)
{
  int nchars, j;
  char datanum[2];

  char line[MAXLINE];
  char strtbl[NLINES][MAXLINE];	// 4 lines, 5 words with an additional null
  char (*nxt_string)[MAXLINE] = strtbl;

  char msg[] = "Enter 4 words, separated by ENTER, each maximum 5 characters.";

  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART2_UART_Init();

  HAL_UART_Receive_IT(&huart2, (uint8_t *)Buffer, 1);  // UART interrupt starts

  HAL_UART_Transmit(&huart2, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);
  HAL_UART_Transmit(&huart2, (uint8_t *)"\n\r", 2, HAL_MAX_DELAY);

  for (j=0; j<NLINES; j++)
  {
		 nchars = get_line(line, MAXLINE);
	     HAL_UART_Transmit(&huart2, (uint8_t *)"\n\r", 2, HAL_MAX_DELAY);  // new line

	     itoa(nchars, datanum, 10);	// Convert integer to ascii. Needs stdlib.h
	     HAL_UART_Transmit(&huart2, (uint8_t *)datanum, strlen(datanum), HAL_MAX_DELAY);
	     HAL_UART_Transmit(&huart2, (uint8_t *)" letters entered as", 19, HAL_MAX_DELAY);
	     strcpy(*nxt_string, line);
	     HAL_UART_Transmit(&huart2, (uint8_t *)"\n\r", 2, HAL_MAX_DELAY);  // new line
	     HAL_UART_Transmit(&huart2, (uint8_t *)*nxt_string, strlen(*nxt_string), HAL_MAX_DELAY);

	     HAL_UART_Transmit(&huart2, (uint8_t *)"\n\n\r", 3, HAL_MAX_DELAY);  // 2 line space

	     nxt_string++;		// used a pointer to character array (string)
		 flags &= ~ Done;
  }

  HAL_UART_Transmit(&huart2, (uint8_t *)"\n\n\n\r", 4, HAL_MAX_DELAY);  // 2 line space
  HAL_UART_Transmit(&huart2, (uint8_t *)"You entered:", 12, HAL_MAX_DELAY);
  HAL_UART_Transmit(&huart2, (uint8_t *)"\n\r", 2, HAL_MAX_DELAY);  // new line

  for (j=4; j>0; j--)
  {
    HAL_UART_Transmit(&huart2, (uint8_t *)*(nxt_string-j), strlen(*(nxt_string-j)), HAL_MAX_DELAY);
    // // used a pointer to character array (string)
    HAL_UART_Transmit(&huart2, (uint8_t *)"\n\r", 2, HAL_MAX_DELAY);  // new line
  }

  while (1)	// Stay here forever
	  ;;
}
