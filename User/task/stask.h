#ifndef __STASK_H
#define __STASK_H
#include "stm32f10x.h"
#include "board.h"

struct task_t
{
    uint8_t id;     //�����־��ţ����һ������TASK_SOFT_TIMER
    uint8_t flags;  //�Ƿ����б�־�� ALWAYS_ALIVE:ʼ��ѭ����UNALIVE:�����п�ͨ����������
    void *args;     //�������в���
    void (*handle)(void *args);//�������лص�����
};

enum
{
	  TASK_SOFT_TIMER = 0x00,  //ticker������
//	  TASK_SCAN_KEY   = 0x01,
//		TASK_SCAN_USART = 0x02 ,
//	  TASK_SCAN_RADIO = 0x03 ,
};


void spTaskStart(uint8_t task_id);
void spTaskStop(uint8_t task_id);
void spTaskScheduler(void);



#endif


