#ifndef EVENT_SUPPLY_H
#define EVENT_SUPPLY_H

#include "fsm.h"

// 补给事件
class SupplyEvent : public Event
{
public:
    SupplyEvent(FSM* fsm);
    void init();                                                    // 初始化，对应状态和处理函数的映射

    int supply();
    int supplying();
    int supply_success();
    int not_allow_supply();

    void OnEventEnter();
    void OnEventHandle(int cur_state);
    void OnEventExit();

private:
    std::unordered_map<int, int(SupplyEvent::*)()> e_state;         // 参数1是状态，参数2是处理函数
};

// 停止补给事件
class StopSupplyEvent : public Event
{
public:
    StopSupplyEvent(FSM* fsm);
    void init();                                                    // 初始化，对应状态和处理函数的映射

    int stop_supply();
    int stop_supplying();
    int stop_supply_success();
    int not_allow_stop_supply();

    void OnEventEnter();
    void OnEventHandle(int cur_state);
    void OnEventExit();

private:
    std::unordered_map<int, int(StopSupplyEvent::*)()> e_state;     // 参数1是状态，参数2是处理函数
};

#endif // EVENT_SUPPLY_H
