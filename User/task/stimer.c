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
�������� �� _timer_led_red_cb
��    �� �� 1s��ʱ���ص�����
��    �� �� void
�� �� ֵ �� void
��    �� �� 
*************************************************/
static void _timer_ReceiveServerData_cb(void *args)
{
   // Receive_Server_Data();
}


/************************************************
�������� �� _timer_led_blue_cb
��    �� �� 5s��ʱ���ص�����
��    �� �� void
�� �� ֵ �� void
��    �� ��
*************************************************/
static void _timer_UploadData_cb(void *args)
{
   // Upload_Data();
}


/************************************************
�������� �� _timer_led_green_cb
��    �� �� 10s��ʱ���ص�����
��    �� �� void
�� �� ֵ �� void
��    �� ��
*************************************************/
static void _timer_SendData_cb(void *args)
{
  //  send_data(UploadData);
}


/************************************************
�������� �� stimerlist
��    �� �� ��ʱ���б�
��    �� ��
�� �� ֵ ��
��    �� �� 
*************************************************/
struct stimer_t  stimerlist[] =
{
    creat_timer( STIMER_ReceiveServerData,	  ALIVE,	  1,   ALWAYS_ALIVE, NULL,	_timer_ReceiveServerData_cb 	    ),
    creat_timer( STIMER_UploadData,	ALIVE,	  5,  ALWAYS_ALIVE, NULL,	_timer_UploadData_cb 	    ),
    creat_timer( STIMER_SendData,	ALIVE,	  10,  ALWAYS_ALIVE, NULL,	_timer_SendData_cb 	  ),

};

/************************************************
�������� �� _getTimerTaskNum
��    �� �� ���ݶ�ʱ��id��ѯ�ö�ʱ���ڶ�ʱ�б��е����
��    �� �� ��ʱ��Id
�� �� ֵ �� uint8_t
��    �� �� 
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
�������� �� spTimerStart
��    �� �� ��ʼ��ʱ����
��    �� �� timer_id:��ʱ��id��time��ʱʱ�䣬 num�����д���
�� �� ֵ �� void
��    �� �� 
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
�������� �� spTimerStop
��    �� �� �رն�ʱ��
��    �� �� timer_id:��ʱ��id
�� �� ֵ �� void
��    �� �� 
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
�������� �� spTimerTickerHandle
��    �� �� ��ʱ��ʱ�������
��    �� �� void
�� �� ֵ �� void
��    �� �� 
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
�������� �� spTimerTaskScheduler
��    �� �� ��ѯ��ʱ�б�����״ִ̬������
��    �� �� void *args
�� �� ֵ �� void
��    �� �� 
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



