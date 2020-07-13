#ifndef __STASK_H
#define __STASK_H
#include "stm32f10x.h"
#include "board.h"

struct task_t
{
    uint8_t id;     //任务标志编号，如第一步中添TASK_SOFT_TIMER
    uint8_t flags;  //是否运行标志， ALWAYS_ALIVE:始终循环，UNALIVE:不运行可通过函数启动
    void *args;     //任务运行参数
    void (*handle)(void *args);//任务运行回调函数
};

enum
{
	  TASK_SOFT_TIMER = 0x00,  //ticker任务函数
//	  TASK_SCAN_KEY   = 0x01,
//		TASK_SCAN_USART = 0x02 ,
//	  TASK_SCAN_RADIO = 0x03 ,
};


void spTaskStart(uint8_t task_id);
void spTaskStop(uint8_t task_id);
void spTaskScheduler(void);



#endif


