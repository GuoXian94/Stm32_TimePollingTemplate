#include "stask.h"
 
 
#define  spTASK_SIZE(array) (sizeof(array)/sizeof(*array))
#define  TASK_INVALID  0xFF


enum
{
        UNALIVE      = 0x00, 
        ALIVE        = 0x01,
        ALWAYS_ALIVE = 0xFF,
};



/************************************************
函数名称 ： _task_soft_timer_cb
功    能 ： 定时任务的回调函数
参    数 ： void
返 回 值 ： 无
作    者 ：
*************************************************/
 void _task_soft_timer_cb(void *args)
{
	  spTimerTaskScheduler(NULL);
}


/************************************************
函数名称 ： tasklist
功    能 ： 任务列表
参    数 ： 
返 回 值 ： 
作    者 ： 
*************************************************/
struct task_t tasklist[] =
{
	 { TASK_SOFT_TIMER,		ALWAYS_ALIVE,	 NULL,	_task_soft_timer_cb 	}, //时间管理任务，请勿删除
//	 { TASK_SCAN_KEY,		ALWAYS_ALIVE,	 NULL,	_task_scan_key_cb     	}, 
//	 { TASK_SCAN_USART,		ALWAYS_ALIVE,	 NULL,	_task_scan_usart_cb   	}, 
//	 { TASK_SCAN_RADIO,		ALWAYS_ALIVE,	 NULL,	_task_scan_radio_cb   	}, //无线Sx1278任务管理
};


/************************************************
函数名称 ： _getTaskNum
功    能 ： 获取指定任务在任务列表中的位置
参    数 ： 任务号
返 回 值 ： 任务Id号
作    者 ： 
*************************************************/
static uint8_t _getTaskNum (uint8_t task_id)
{
   uint8_t i;
   for (i = 0; i < spTASK_SIZE(tasklist); ++i)
   {
     if(tasklist[i].id == task_id )
		 {
		   return i;
		 }
   }
	 return TASK_INVALID;
}

/************************************************
函数名称 ： spTaskStart
功    能 ： 开始指定任务
参    数 ： 任务号
返 回 值 ： 无
作    者 ： 
*************************************************/
void spTaskStart(uint8_t task_id)
{
  uint8_t t_id;
	t_id = _getTaskNum(task_id);
	if(t_id == TASK_INVALID )
	{
		return;
	}
	tasklist[t_id].flags = ALIVE;
}
/************************************************
函数名称 ： spTaskStop
功    能 ： 停止指定任务
参    数 ： 任务号
返 回 值 ： 无
作    者 ： sun
*************************************************/
void spTaskStop(uint8_t task_id)
{
  uint8_t t_id;
	t_id = _getTaskNum(task_id);
	if(t_id == TASK_INVALID )
	{
		return;
	}
	tasklist[t_id].flags = UNALIVE;
}

/************************************************
函数名称 ： spTaskScheduler
功    能 ： 轮训任务列表中的任务,任务分配器
参    数 ： void
返 回 值 ： void
作    者 ：
*************************************************/
void spTaskScheduler(void)
{
	uint8_t i;
	for (i = 0; i < spTASK_SIZE(tasklist); ++i)
	{
		if (tasklist[i].flags != UNALIVE ) 
		{
			if(tasklist[i].flags != ALWAYS_ALIVE ) 
			{
				tasklist[i].flags = UNALIVE;
				tasklist[i].handle(tasklist[i].args);
			}
			else
			{
				tasklist[i].handle(tasklist[i].args);
			}
		}
	}
}

