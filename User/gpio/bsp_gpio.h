#ifndef __BSP_GPIO_H
#define __BSP_GPIO_H
#include "stm32f10x.h"

#define LED_GPIO_PORT    	GPIOB			              /* GPIO�˿� */
#define LED_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO�˿�ʱ�� */
#define LED_GPIO_PIN		GPIO_Pin_5			        /* ���ӵ�SCLʱ���ߵ�GPIO */

void led_off(void);
void led_on(void);
void LED_GPIO_Config(void); 
#endif
