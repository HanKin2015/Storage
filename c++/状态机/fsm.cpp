#include "fsm.h"

// 注册新的事件
bool FSM::RegisterEvent(int event, Event *pEvent)
{
    all_event[event] = pEvent;
    return true;
}

// 需要状态转移则调用此函数
bool FSM::StateTrans(int newState)
{
    cur_state = newState;
    return true;
}

// 根据事件，调用对应的事件类处理函数去处理
void FSM::EventTick(int event)
{
    all_event[event]->OnEventHandle(cur_state);
}

// 获取当前状态
int FSM::GetCurState()
{
    return cur_state;
}

// 设置初始状态
void FSM::SetInitState(int state)
{
    cur_state = state;
}

