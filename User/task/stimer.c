#include "stimer.h"

#define spTIMER_SIZE(array) (sizeof(array)/sizeof(*array))
#define creat_timer(timer_id, state, expires,          runs,arg, handler) \
                   {timer_id, state, expires,expires,  runs,arg, handler}
#define   TASK_INVALID      0xFF
#define   ALWAYS_ALIVE      0xFFFF
#define   ALWAYS_UNLIVE     0x0000

enum
{
    UNALIVE      = 0x00,
    ALIVE        = 0x01,
};


/************************************************
函数名称 ： _timer_led_red_cb
功    能 ： 1s定时器回调函数
参    数 ： void
返 回 值 ： void
作    者 ： 
*************************************************/
static void _timer_ReceiveServerData_cb(void *args)
{
   // Receive_Server_Data();
}


/************************************************
函数名称 ： _timer_led_blue_cb
功    能 ： 5s定时器回调函数
参    数 ： void
返 回 值 ： void
作    者 ：
*************************************************/
static void _timer_UploadData_cb(void *args)
{
   // Upload_Data();
}


/************************************************
函数名称 ： _timer_led_green_cb
功    能 ： 10s定时器回调函数
参    数 ： void
返 回 值 ： void
作    者 ：
*************************************************/
static void _timer_SendData_cb(void *args)
{
  //  send_data(UploadData);
}


/************************************************
函数名称 ： stimerlist
功    能 ： 定时器列表
参    数 ：
返 回 值 ：
作    者 ： 
*************************************************/
struct stimer_t  stimerlist[] =
{
    creat_timer( STIMER_ReceiveServerData,	  ALIVE,	  1,   ALWAYS_ALIVE, NULL,	_timer_ReceiveServerData_cb 	    ),
    creat_timer( STIMER_UploadData,	ALIVE,	  5,  ALWAYS_ALIVE, NULL,	_timer_UploadData_cb 	    ),
    creat_timer( STIMER_SendData,	ALIVE,	  10,  ALWAYS_ALIVE, NULL,	_timer_SendData_cb 	  ),

};

/************************************************
函数名称 ： _getTimerTaskNum
功    能 ： 根据定时器id查询该定时器在定时列表中的序号
参    数 ： 定时器Id
返 回 值 ： uint8_t
作    者 ： 
*************************************************/
static uint8_t _getTimerTaskNum (uint8_t timer_id)
{
    uint8_t i;
    for (i = 0; i < spTIMER_SIZE(stimerlist); ++i)
    {
        if(stimerlist[i].id == timer_id )
        {
            return i;
        }
    }
    return TASK_INVALID;
}
/************************************************
函数名称 ： spTimerStart
功    能 ： 开始定时任务
参    数 ： timer_id:定时器id，time定时时间， num，运行次数
返 回 值 ： void
作    者 ： 
*************************************************/
void spTimerStart(uint8_t timer_id,uint32_t time,uint16_t num)
{
    uint8_t t_id;
    double timeTmp = 0;
    t_id = _getTimerTaskNum(timer_id);
    if(t_id == TASK_INVALID )
    {
        return;
    }
    timeTmp = 1000.00/TICK_RATE_HZ;
    timeTmp = time/timeTmp;
    time = (uint32_t )timeTmp;
    stimerlist[t_id].expires = time;
    stimerlist[t_id].expires_t = time;
    stimerlist[t_id].runs = num;
}

/************************************************
函数名称 ： spTimerStop
功    能 ： 关闭定时器
参    数 ： timer_id:定时器id
返 回 值 ： void
作    者 ： 
*************************************************/
void spTimerStop(uint8_t timer_id)
{
    uint8_t t_id;
    t_id = _getTimerTaskNum(timer_id);
    if(t_id == TASK_INVALID )
    {
        return;
    }
    stimerlist[t_id].flags = UNALIVE;
    stimerlist[t_id].runs = ALWAYS_UNLIVE;
}

/************************************************
函数名称 ： spTimerTickerHandle
功    能 ： 定时器时间管理句柄
参    数 ： void
返 回 值 ： void
作    者 ： 
*************************************************/
void spTimerTickerHandle(void)
{
    uint8_t i;
    static uint32_t temp = 0;
    if(spGetTickCount() == temp)
    {
        return ;
    }
    for (i = 0; i < spTIMER_SIZE(stimerlist); ++i)
    {
        if (stimerlist[i].runs != ALWAYS_UNLIVE)
        {
            if(stimerlist[i].expires > 0)
            {
                --stimerlist[i].expires;
                if(stimerlist[i].expires ==0)
                {
                     stimerlist[i].flags = ALIVE;
                }
            }
//            else
//            {
//                stimerlist[i].expires = 0;
//                stimerlist[i].flags = ALIVE;
//            }
        }
    }
    temp = spGetTickCount();
}

/************************************************
函数名称 ： spTimerTaskScheduler
功    能 ： 轮询定时列表，根据状态执行任务
参    数 ： void *args
返 回 值 ： void
作    者 ： 
*************************************************/
void spTimerTaskScheduler(void *args)
{
    uint8_t i;
    for (i = 0; i < spTIMER_SIZE(stimerlist); ++i)
    {
        if (stimerlist[i].flags == ALIVE)
        {
            if (stimerlist[i].runs == ALWAYS_UNLIVE)
            {
                stimerlist[i].flags = UNALIVE;
                stimerlist[i].expires = 0;
                continue;
            }
            else if (stimerlist[i].runs == ALWAYS_ALIVE)
            {
                stimerlist[i].flags = UNALIVE;
                stimerlist[i].timer_cb(stimerlist[i].args);
                stimerlist[i].expires = stimerlist[i].expires_t;
            }
            else
            {
                stimerlist[i].runs --;
                stimerlist[i].flags = UNALIVE;
                stimerlist[i].timer_cb(stimerlist[i].args);
                stimerlist[i].expires = stimerlist[i].expires_t;
            }

        }

    }
}



