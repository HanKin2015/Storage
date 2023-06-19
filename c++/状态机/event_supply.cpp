#include <iostream>
#include <unistd.h>
#include "event_supply.h"

using namespace std;

SupplyEvent::SupplyEvent(FSM* fsm) : Event(fsm) 
{
    init();
}

// 初始化，对应状态和处理函数的映射
void SupplyEvent::init()
{
    e_state[IDLE_STATE]                 = &SupplyEvent::not_allow_supply;
    e_state[CONNECTING_STATE]           = &SupplyEvent::not_allow_supply;
    e_state[CONNECT_SUCCESS_STATE]      = &SupplyEvent::supply;
    e_state[CONNECT_FAIL_STATE]         = &SupplyEvent::not_allow_supply;
    e_state[SUPPLYING_STATE]            = &SupplyEvent::supplying;
    e_state[SUPPLY_SUCCESS_STATE]       = &SupplyEvent::supply_success;
    e_state[SUPPLY_FAIL_STATE]          = &SupplyEvent::supply;
    e_state[STOP_SUPPLYING_STATE]       = &SupplyEvent::not_allow_supply;
    e_state[STOP_SUPPLY_SUCCESS_STATE]  = &SupplyEvent::supply_success;
    e_state[STOP_SUPPLY_FAIL_STATE]     = &SupplyEvent::supply;
    e_state[DISCONNECTING_STATE]        = &SupplyEvent::not_allow_supply;
}

// 补给处理
int SupplyEvent::supply()
{   
    cout << "supply start" << endl;
    fsm->StateTrans(SUPPLYING_STATE);
    sleep(3);
    fsm->StateTrans(SUPPLY_SUCCESS_STATE);
    cout << "supply success" << endl;
    return 0;
}

// 补给中处理
int SupplyEvent::supplying()
{
    cout << "supplying" << endl;
    return 0;
}

// 补给成功处理
int SupplyEvent::supply_success()
{
    cout << "supply_success" << endl;
    return 0;
}

// 不能补给处理
int SupplyEvent::not_allow_supply()
{
    cout << "not_allow_supply" << endl;
    return 0;
}

// 事件资源申请处理
void SupplyEvent::OnEventEnter() 
{
    cout << "---- SupplyEvent Enter" << endl;
}

// 事件处理
void SupplyEvent::OnEventHandle(int cur_state) 
{
    cout << "OnEventHandle cur state: " << cur_state << endl;
    OnEventEnter();

    (this->*e_state[cur_state])();                  // 不加this会编译出错

    OnEventExit();
    return ;  
}

// 事件资源释放处理
void SupplyEvent::OnEventExit() 
{ 
    cout << "==== SupplyEvent Exit" << endl; 
}




StopSupplyEvent::StopSupplyEvent(FSM* fsm) : Event(fsm) 
{
    init();
}

// 初始化，对应状态和处理函数的映射
void StopSupplyEvent::init()
{
    e_state[IDLE_STATE]                 = &StopSupplyEvent::not_allow_stop_supply;
    e_state[CONNECTING_STATE]           = &StopSupplyEvent::not_allow_stop_supply;
    e_state[CONNECT_SUCCESS_STATE]      = &StopSupplyEvent::not_allow_stop_supply;
    e_state[CONNECT_FAIL_STATE]         = &StopSupplyEvent::not_allow_stop_supply;
    e_state[SUPPLYING_STATE]            = &StopSupplyEvent::stop_supply;
    e_state[SUPPLY_SUCCESS_STATE]       = &StopSupplyEvent::stop_supply;
    e_state[SUPPLY_FAIL_STATE]          = &StopSupplyEvent::stop_supply;
    e_state[STOP_SUPPLYING_STATE]       = &StopSupplyEvent::stop_supplying;
    e_state[STOP_SUPPLY_SUCCESS_STATE]  = &StopSupplyEvent::stop_supply_success;
    e_state[STOP_SUPPLY_FAIL_STATE]     = &StopSupplyEvent::stop_supply;
    e_state[DISCONNECTING_STATE]        = &StopSupplyEvent::not_allow_stop_supply;
}

// 补给处理
int StopSupplyEvent::stop_supply()
{   
    cout << "stop_supply start" << endl;
    fsm->StateTrans(STOP_SUPPLYING_STATE);
    sleep(3);
    fsm->StateTrans(STOP_SUPPLY_SUCCESS_STATE);
    cout << "stop_supply success" << endl;
    return 0;
}

// 补给中处理
int StopSupplyEvent::stop_supplying()
{
    cout << "stop_supplying" << endl;
    return 0;
}

// 补给成功处理
int StopSupplyEvent::stop_supply_success()
{
    cout << "stop_supply_success" << endl;
    return 0;
}

// 不能补给处理
int StopSupplyEvent::not_allow_stop_supply()
{
    cout << "not_allow_supply" << endl;
    return 0;
}

// 事件资源申请处理
void StopSupplyEvent::OnEventEnter() 
{
    cout << "---- StopSupplyEvent Enter" << endl;
}

// 事件处理
void StopSupplyEvent::OnEventHandle(int cur_state) 
{
    cout << "OnEventHandle cur state: " << cur_state << endl;
    OnEventEnter();

    (this->*e_state[cur_state])();                  // 不加this会编译出错

    OnEventExit();
    return ;  
}

// 事件资源释放处理
void StopSupplyEvent::OnEventExit() 
{ 
    cout << "==== StopSupplyEvent Exit" << endl; 
}

