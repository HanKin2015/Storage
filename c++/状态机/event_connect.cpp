#include <iostream>
#include <unistd.h>
#include "event_connect.h"

using namespace std;

ConnectEvent::ConnectEvent(FSM* fsm) : Event(fsm) 
{
    init();
}

// 初始化，对应状态和处理函数的映射
void ConnectEvent::init()
{
    e_state[IDLE_STATE]                 = &ConnectEvent::connect;
    e_state[CONNECTING_STATE]           = &ConnectEvent::connecting;
    e_state[CONNECT_SUCCESS_STATE]      = &ConnectEvent::connect_success;
    e_state[CONNECT_FAIL_STATE]         = &ConnectEvent::connect;
    e_state[SUPPLYING_STATE]            = &ConnectEvent::connect_success;
    e_state[SUPPLY_SUCCESS_STATE]       = &ConnectEvent::connect_success;
    e_state[SUPPLY_FAIL_STATE]          = &ConnectEvent::connect_success;
    e_state[STOP_SUPPLYING_STATE]       = &ConnectEvent::connect_success;
    e_state[STOP_SUPPLY_SUCCESS_STATE]  = &ConnectEvent::connect_success;
    e_state[STOP_SUPPLY_FAIL_STATE]     = &ConnectEvent::connect_success;
    e_state[DISCONNECTING_STATE]        = &ConnectEvent::connect_success;
}

// 连接处理
int ConnectEvent::connect()
{   
    cout << "connect start" << endl;
    fsm->StateTrans(CONNECTING_STATE);
    sleep(3);
    fsm->StateTrans(CONNECT_SUCCESS_STATE);
    cout << "connect success" << endl;
    return 0;
}

// 连接中处理
int ConnectEvent::connecting()
{
    cout << "connecting" << endl;
    return 0;
}

// 连接成功处理
int ConnectEvent::connect_success()
{
    cout << "connect_success" << endl;
    return 0;
}

// 事件资源申请处理
void ConnectEvent::OnEventEnter() 
{
    cout << "---- ConnectEvent Enter" << endl;
}

// 事件处理
void ConnectEvent::OnEventHandle(int cur_state) 
{
    cout << "OnEventHandle cur state: " << cur_state << endl;
    OnEventEnter();

    (this->*e_state[cur_state])();                  // 不加this会编译出错

    OnEventExit();
    return ;  
}

// 事件资源释放处理
void ConnectEvent::OnEventExit() 
{ 
    cout << "==== ConnectEvent Exit" << endl; 
}





DisconnectEvent::DisconnectEvent(FSM* fsm) : Event(fsm) 
{
    init();
}

// 初始化，对应状态和处理函数的映射
void DisconnectEvent::init()
{
    e_state[IDLE_STATE]                 = &DisconnectEvent::disconnect_success;
    e_state[CONNECTING_STATE]           = &DisconnectEvent::disconnect;
    e_state[CONNECT_SUCCESS_STATE]      = &DisconnectEvent::disconnect;
    e_state[CONNECT_FAIL_STATE]         = &DisconnectEvent::disconnect_success;
    e_state[SUPPLYING_STATE]            = &DisconnectEvent::disconnect;
    e_state[SUPPLY_SUCCESS_STATE]       = &DisconnectEvent::disconnect;
    e_state[SUPPLY_FAIL_STATE]          = &DisconnectEvent::disconnect;
    e_state[STOP_SUPPLYING_STATE]       = &DisconnectEvent::disconnect;
    e_state[STOP_SUPPLY_SUCCESS_STATE]  = &DisconnectEvent::disconnect;
    e_state[STOP_SUPPLY_FAIL_STATE]     = &DisconnectEvent::disconnect;
    e_state[DISCONNECTING_STATE]        = &DisconnectEvent::disconnecting;
}

// 断开连接处理
int DisconnectEvent::disconnect()
{   
    cout << "disconnect start" << endl;
    fsm->StateTrans(DISCONNECTING_STATE);
    sleep(3);
    fsm->StateTrans(IDLE_STATE);
    cout << "disconnect success" << endl;
    return 0;
}

// 断开连接中处理
int DisconnectEvent::disconnecting()
{
    cout << "disconnecting" << endl;
    return 0;
}

// 断开连接成功处理
int DisconnectEvent::disconnect_success()
{
    cout << "disconnect_success" << endl;
    return 0;
}

// 事件资源申请处理
void DisconnectEvent::OnEventEnter() 
{
    cout << "---- DisconnectEvent Enter" << endl;
}

// 事件处理
void DisconnectEvent::OnEventHandle(int cur_state) 
{
    cout << "OnEventHandle cur state: " << cur_state << endl;
    OnEventEnter();

    (this->*e_state[cur_state])();                  // 不加this会编译出错

    OnEventExit();
    return ;  
}

// 事件资源释放处理
void DisconnectEvent::OnEventExit() 
{ 
    cout << "==== DisconnectEvent Exit" << endl; 
}
