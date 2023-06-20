/**
* 文 件 名: main.cpp
* 文件描述: 探究读写文件速度效率
* 备    注：https://blog.csdn.net/qq_30519005/article/details/122562055
* 作    者: HanKin
* 创建日期: 2023.06.19
* 修改日期：2023.06.19
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

/************************************************************************************
* 状态是固定的，事件是可扩展的
* 状态模式实现状态机
* 状态机类管理状态转换，以及状态处理调用
* 事件业务逻辑处理类
* 
*                 空闲  对接中  对接成功  对接失败  补给中  补给成功  补给失败  停止补给中  停止补给成功  停止补给失败  断开对接中
* 对接事件
* 断开对接事件
* 补给事件
* 停止补给事件
*************************************************************************************/

#include <iostream>
#include "event_connect.h"
#include "event_supply.h"

int main()
{
    // 构造状态机
    FSM* fsm = new FSM();
    fsm->SetInitState(IDLE_STATE);

    Event* connect_e = new ConnectEvent(fsm);
    Event* disconnect_e = new DisconnectEvent(fsm);
    Event* supply_e = new SupplyEvent(fsm);
    Event* stop_supply_e = new StopSupplyEvent(fsm);

    fsm->RegisterEvent(CONNECT_EVENT, connect_e);
    fsm->RegisterEvent(DISCONNECT_EVENT, disconnect_e);
    fsm->RegisterEvent(SUPPLY_EVENT, supply_e);
    fsm->RegisterEvent(STOP_SUPPLY_EVENT, stop_supply_e);

    fsm->EventTick(CONNECT_EVENT);
    fsm->EventTick(CONNECT_EVENT);
    fsm->EventTick(SUPPLY_EVENT);
    fsm->EventTick(STOP_SUPPLY_EVENT);

    fsm->EventTick(DISCONNECT_EVENT);

    std::cout << "cur state: " << fsm->GetCurState() << std::endl;
    return 0;
}
