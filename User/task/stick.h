#ifndef __STICK_H
#define __STICK_H
#include "stm32f10x.h"
#include "board.h"


#define TICK_RATE_HZ   1000//1000 //ϵͳ����Ƶ����Ҫ��

void spTickCount(void);
uint32_t spGetTickCount(void);
#endif
