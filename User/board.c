#include "board.h"

void board_init()
{
 
     delay_init();       //Delay function initialization
     USART1_Init_Config(115200);
     USART2_Init_Config(115200);
     USART3_Init_Config(115200);
     LED_GPIO_Config();

}



