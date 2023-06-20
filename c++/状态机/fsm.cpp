#include "fsm.h"

/**
* @brief 服务端传过来的消息类型的字符串描述
* @param state 消息类型
* @return 消息类型的字符串，如果未知类型则返回unknown state
*/
const char *state2str(int state)
{
    static const char *__state_str[DISCONNECTING_STATE - IDLE_STATE + 1] =
    {
        "空闲",
        "对接中",
        "对接成功",
        "对接失败",
        "补给中",
        "补给成功",
        "补给失败",
        "停止补给中",
        "停止补给成功",
        "停止补给失败",
        "断开对接中",
    };

    if (state < IDLE_STATE || state > DISCONNECTING_STATE)
        return "unknown state";

    return __state_str[state - IDLE_STATE];
}

/**
* @brief 服务端传过来的消息类型的字符串描述
* @param event 消息类型
* @return 消息类型的字符串，如果未知类型则返回unknown event
*/
const char *event2str(int event)
{
    static const char *__event_str[STOP_SUPPLY_EVENT - CONNECT_EVENT + 1] =
    {
        "连接事件",
        "断开连接",
        "补给事件",
        "停止补给",
    };

    if (event < CONNECT_EVENT || event > STOP_SUPPLY_EVENT)
        return "unknown event";

    return __event_str[event - CONNECT_EVENT];
}

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

