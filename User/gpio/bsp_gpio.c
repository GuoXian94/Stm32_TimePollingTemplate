#include "bsp_gpio.h"   

 /**
  * @brief  ��ʼ������LED��IO
  * @param  ��
  * @retval ��
  */
void LED_GPIO_Config(void)
{		
		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*����LED��ص�GPIO����ʱ��*/
		RCC_APB2PeriphClockCmd( LED_GPIO_CLK, ENABLE);
		/*ѡ��Ҫ���Ƶ�GPIO����*/
		GPIO_InitStructure.GPIO_Pin = LED_GPIO_PIN;	

		/*��������ģʽΪͨ���������*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*������������Ϊ50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*���ÿ⺯������ʼ��GPIO*/
		GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);	
		GPIO_SetBits(LED_GPIO_PORT,LED_GPIO_PIN);
		
}
void led_off(void)
{

  GPIO_SetBits(LED_GPIO_PORT,LED_GPIO_PIN);

}

void led_on(void)
{
 GPIO_ResetBits(LED_GPIO_PORT,LED_GPIO_PIN);


}
/*********************************************END OF FILE**********************/




