#ifndef EVENT_CONNECT_H
#define EVENT_CONNECT_H

#include "fsm.h"

// 连接事件
class ConnectEvent : public Event
{
public:
    ConnectEvent(FSM* fsm);
    void init();                                                    // 初始化，对应状态和处理函数的映射

    int connect();
    int connecting();
    int connect_success();

    void OnEventEnter();
    void OnEventHandle(int cur_state);
    void OnEventExit();

private:
    std::unordered_map<int, int(ConnectEvent::*)()> e_state;        // 参数1是状态，参数2是处理函数
};

// 断开连接事件
class DisconnectEvent : public Event
{
public:
    DisconnectEvent(FSM* fsm);
    void init();                                                    // 初始化，对应状态和处理函数的映射

    int disconnect();
    int disconnecting();
    int disconnect_success();

    void OnEventEnter();
    void OnEventHandle(int cur_state);
    void OnEventExit();

private:
    std::unordered_map<int, int(DisconnectEvent::*)()> e_state;     // 参数1是状态，参数2是处理函数
};

#endif // EVENT_CONNECT_H
