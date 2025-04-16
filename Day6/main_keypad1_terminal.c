// This exercise will turn the LED on whenever a key(keypad) is pushed an output to terminal
#include "main.h"

#define Number_of_Keys 12
#define Number_of_Cols  3
#define PA0 0x0001
#define PA1 0x0002
#define PA4 0x0010
#define PB0 0x0001
#define PC1 0x0002
#define PC0 0x0001
#define PA10 0x0400

#define KeyDetect 0x0001

typedef struct
{
   unsigned short sKeyRead;
   unsigned short sKeyReadTempPos;
   unsigned short sKeySend;
   unsigned short sKeyCol;
   char KeyLetter;
   unsigned short sKeyCommand;
} Key_Contorl_struct_t;

typedef enum KeyName
{
  ONE_command,
  FOUR_command,
  SEVEN_command,
  STAR_command,
  TWO_command,
  FIVE_command,
  EIGHT_command,
  ZERO_command,
  THREE_command,
  SIX_command,
  NINE_command,
  POUND_command
} KeyName;

/******** Structure *******/
Key_Contorl_struct_t sKeyControl[Number_of_Keys]
={
 {PA10,0x8,PA4,0,'1',ONE_command},     // PA10 (read), PA4 (send)
 {PC0,0x4,PA4,0,'4',FOUR_command},     // PC0 (read), PA4 (send)
 {PC1,0x2,PA4,0,'7',SEVEN_command},    // PC1 (read), PA4 (send)
 {PB0,0x1,PA4,0,'*',STAR_command},     // PB0 (read), PA4 (send)

 {PA10,0x8,PA1,1,'2',TWO_command},     // PA10 (read), PA1 (send)
 {PC0,0x4,PA1,1,'5',FIVE_command},     // PC0 (read), PA1 (send)
 {PC1,0x2,PA1,1,'8',EIGHT_command},    // PC1 (read), PA1 (send)
 {PB0,0x1,PA1,1,'0',ZERO_command},     // PB0 (read), PA1 (send)

 {PA10,0x8,PA0,2,'3',THREE_command},   // PA10 (read), PA0 (send)
 {PC0,0x4,PA0,2,'6',SIX_command},      // PC0 (read), PA0 (send)
 {PC1,0x2,PA0,2,'9',NINE_command},     // PC1 (read), PA0 (send)
 {PB0,0x1,PA0,2,'#',POUND_command}     // PB0 (read), PA0 (send)
};

unsigned short sKeyStatus;
unsigned short sKeyCurrentCol[Number_of_Cols];
unsigned short sKeyDebouncedCol[Number_of_Cols];
unsigned short sKeyIssued;

UART_HandleTypeDef huart2;

void Keypadscan(void);
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);

int main(void)
{
  unsigned short sIndex;		// This is 16-bit

  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART2_UART_Init();

  GPIOA->ODR &= ~0x0020;        // off LED

  for (sIndex=0; sIndex<Number_of_Cols; sIndex++) // clear all records
  { 
	  sKeyDebouncedCol[sIndex] = 0x0000;
  }

  while (1)
  {
	Keypadscan();				// scan keys
	HAL_Delay(10);				// in every 10ms 

	if ((sKeyStatus & KeyDetect) && (sKeyIssued != 0xFFFF))  // Here is to decode which key entered
	{
		GPIOA->ODR |= 0x0020;	// turn on LED first

		switch (sKeyIssued)		// Use the KeyName to find which key
	    {
	    	case ONE_command:	// Send the found key to terminal
	    	{
	    		HAL_UART_Transmit(&huart2, (uint8_t *)"Key_1", 5, HAL_MAX_DELAY);
	    		HAL_UART_Transmit(&huart2, (uint8_t *)"\n\r", 2, HAL_MAX_DELAY);
		        break;
	    	}
	        case FOUR_command:	// Send the found key to terminal
	    	{
	    		HAL_UART_Transmit(&huart2, (uint8_t *)"Key_4", 5, HAL_MAX_DELAY);
	    		HAL_UART_Transmit(&huart2, (uint8_t *)"\n\r", 2, HAL_MAX_DELAY);
		        break;
	    	}
	        case SEVEN_command:  // Send the found key to terminal
	    	{
	    		HAL_UART_Transmit(&huart2, (uint8_t *)"Key_7", 5, HAL_MAX_DELAY);
	    		HAL_UART_Transmit(&huart2, (uint8_t *)"\n\r", 2, HAL_MAX_DELAY);
		        break;
	    	}
	        case STAR_command:	// Send the found key to terminal
	    	{
	    		HAL_UART_Transmit(&huart2, (uint8_t *)"Key_*", 5, HAL_MAX_DELAY);
	    		HAL_UART_Transmit(&huart2, (uint8_t *)"\n\r", 2, HAL_MAX_DELAY);
		        break;
	    	}
	        case TWO_command:	// Send the found key to terminal
	    	{
	    		HAL_UART_Transmit(&huart2, (uint8_t *)"Key_2", 5, HAL_MAX_DELAY);
	    		HAL_UART_Transmit(&huart2, (uint8_t *)"\n\r", 2, HAL_MAX_DELAY);
		        break;
	    	}
	        case FIVE_command:	// Send the found key to terminal
	    	{
	    		HAL_UART_Transmit(&huart2, (uint8_t *)"Key_5", 5, HAL_MAX_DELAY);
		        HAL_UART_Transmit(&huart2, (uint8_t *)"\n\r", 2, HAL_MAX_DELAY);
		        break;
	    	}
	        case EIGHT_command:	// Send the found key to terminal
	    	{
	    		HAL_UART_Transmit(&huart2, (uint8_t *)"Key_8", 5, HAL_MAX_DELAY);
	    		HAL_UART_Transmit(&huart2, (uint8_t *)"\n\r", 2, HAL_MAX_DELAY);
		        break;
	    	}
	        case ZERO_command:	// Send the found key to terminal
	    	{
	    		HAL_UART_Transmit(&huart2, (uint8_t *)"Key_0", 5, HAL_MAX_DELAY);
	    		HAL_UART_Transmit(&huart2, (uint8_t *)"\n\r", 2, HAL_MAX_DELAY);\
		        break;
	    	}
	        case THREE_command:	// Send the found key to terminal
	    	{
	    		HAL_UART_Transmit(&huart2, (uint8_t *)"Key_3", 5, HAL_MAX_DELAY);
	    		HAL_UART_Transmit(&huart2, (uint8_t *)"\n\r", 2, HAL_MAX_DELAY);
		        break;
	    	}
	        case SIX_command:	// Send the found key to terminal
	    	{
	    		HAL_UART_Transmit(&huart2, (uint8_t *)"Key_6", 5, HAL_MAX_DELAY);
	    		HAL_UART_Transmit(&huart2, (uint8_t *)"\n\r", 2, HAL_MAX_DELAY);
		        break;
	    	}
	        case NINE_command:	// Send the found key to terminal
	    	{
	    		HAL_UART_Transmit(&huart2, (uint8_t *)"Key_9", 5, HAL_MAX_DELAY);
	    		HAL_UART_Transmit(&huart2, (uint8_t *)"\n\r", 2, HAL_MAX_DELAY);
		        break;
	    	}
	        case POUND_command:	// Send the found key to terminal
	        {
	    		HAL_UART_Transmit(&huart2, (uint8_t *)"Key_#", 5, HAL_MAX_DELAY);
	    		HAL_UART_Transmit(&huart2, (uint8_t *)"\n\r", 2, HAL_MAX_DELAY);
		        break;
	        }
            default:
    	}
	}
  }
}


void Keypadscan()
{
    unsigned short sIndex;

    // Clear all key records
    for (sIndex=0; sIndex<Number_of_Cols; sIndex++)
    {
      sKeyCurrentCol[sIndex] = 0x00;
    }

    // Read all 3 column
    for (sIndex=0; sIndex<Number_of_Keys; sIndex++)
    {
      GPIOA->ODR &=~(PA4 | PA1 | PA0);
      GPIOA->ODR |= sKeyControl[sIndex].sKeySend;
      HAL_Delay(0.5);

      switch (sKeyControl[sIndex].sKeyCommand)
	  {
      	  case ONE_command:
      	  case TWO_command:
      	  case THREE_command:
      		if (GPIOA->IDR & sKeyControl[sIndex].sKeyRead)
      		  sKeyCurrentCol[sKeyControl[sIndex].sKeyCol]= sKeyControl[sIndex].sKeyReadTempPos;
      		break;

      	  case FOUR_command:
      	  case FIVE_command:
      	  case SIX_command:
      	  case SEVEN_command:
      	  case EIGHT_command:
      	  case NINE_command:
        	if (GPIOC->IDR & sKeyControl[sIndex].sKeyRead)
        	  sKeyCurrentCol[sKeyControl[sIndex].sKeyCol] = sKeyControl[sIndex].sKeyReadTempPos;
      	    break;

      	  case STAR_command:
      	  case ZERO_command:
      	  case POUND_command:
      		if (GPIOB->IDR & sKeyControl[sIndex].sKeyRead)
      		  sKeyCurrentCol[sKeyControl[sIndex].sKeyCol] = sKeyControl[sIndex].sKeyReadTempPos;
	  }
    }

    // Check if a key is steadily read
    for (sIndex=0; sIndex<Number_of_Cols; sIndex++)
    {
      if ((sKeyCurrentCol[sIndex] == sKeyDebouncedCol[sIndex]) && (sKeyCurrentCol[sIndex] != 0x0000))
        break;
    }

    if (sIndex <Number_of_Cols)
    {
       // Find which key is depressed
       for (sIndex=0 ; sIndex<Number_of_Keys; sIndex++)
       {
         if (sKeyCurrentCol[sKeyControl[sIndex].sKeyCol] & sKeyControl[sIndex].sKeyReadTempPos)
         {
           sKeyIssued = sKeyControl[sIndex].sKeyCommand;
           {
              sKeyStatus |= KeyDetect;
              break;
           }
         }
         else
           sKeyIssued = 0xFFFF;  // This equals negative 1, (-1)
       }
    }
    else
    {
      sKeyStatus &= ~KeyDetect;
    }

    // Transfer Current reading to debounced reading
    for (sIndex=0; sIndex<Number_of_Cols; sIndex++)
    {
      sKeyDebouncedCol[sIndex] = sKeyCurrentCol[sIndex];
    }
}


