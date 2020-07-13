 #ifndef __STIMER_H
#define __STIMER_H
#include "board.h"
#include "stm32f10x.h"

enum
{
	 STIMER_ReceiveServerData   = 0x00,
     STIMER_UploadData  = 0x01, 
     STIMER_SendData = 0x02, 
//	 STIMER_KEY       = 0x03,	
//	 STIMER_USART     = 0x04,	 
};

//定时任务函数
struct stimer_t
{
    uint8_t  id;             //定时任务ID
    uint8_t  flags;          //运行标志
	  uint32_t expires;        //有效时间
		uint32_t expires_t;      //有效时间，用来重装用
		uint16_t runs;
	void *args;
    void (*timer_cb)(void *args);
};

void spTimerStart(uint8_t timer_id,uint32_t time,uint16_t num);
void spTimerStop(uint8_t timer_id);
void spTimerTickerHandle(void);
void spTimerTaskScheduler(void *args);




#endif


