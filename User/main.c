/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ≤‚ ‘led
  ******************************************************************************

  */ 
	

#include "board.h"

int main(void)
{	

    board_init();   //function initialization
    
	while (1)
	{
//     led_on();
//	printf("test_board\r\n");	//ITMª˙÷∆¥Ú”°
//    delay_ms(500);
    spTaskScheduler();  
//    led_off();
//    delay_ms(500);        
	}
}


/*********************************************END OF FILE**********************/
