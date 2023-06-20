#ifndef FSM_H
#define FSM_H

#include <unordered_map>

const char *state2str(int state);
const char *event2str(int event);

// 事件
enum {
     CONNECT_EVENT     = 1,             // 连接事件
     DISCONNECT_EVENT  = 2,             // 断开连接
     SUPPLY_EVENT      = 3,             // 补给事件
     STOP_SUPPLY_EVENT = 4,             // 停止补给
};

// 状态
enum {
    IDLE_STATE = 0,                     // 空闲
    
    CONNECTING_STATE,                   // 对接中
    CONNECT_SUCCESS_STATE,              // 对接成功
    CONNECT_FAIL_STATE,                 // 对接失败

    SUPPLYING_STATE,                    // 补给中
    SUPPLY_SUCCESS_STATE,               // 补给成功
    SUPPLY_FAIL_STATE,                  // 补给失败

    STOP_SUPPLYING_STATE,               // 停止补给中
    STOP_SUPPLY_SUCCESS_STATE,          // 停止补给成功
    STOP_SUPPLY_FAIL_STATE,             // 停止补给失败

    DISCONNECTING_STATE,                // 断开对接中
};

class Event;

// FSM类管理事件处理
// 事件类管理状态处理
class FSM
{
public:
    bool RegisterEvent(int event, Event *pEvent);       // 注册新的事件
    bool StateTrans(int newState);                      // 需要状态转移则调用此函数
    void EventTick(int event);                          // 根据事件，调用对应的事件类处理函数去处理
    int GetCurState();                                  // 获取当前状态
    void SetInitState(int state);                       // 设置初始状态

private:
    std::unordered_map<int, Event*> all_event;          // 参数1事件，参数2对应事件类
    int cur_state;                                      // 当前状态
};

// 事件的基类
class Event
{
public:
    
    
    virtual void init() = 0;
    virtual void OnEventEnter() = 0;                        
    virtual void OnEventHandle(int cur_state) = 0;
    virtual void OnEventExit() = 0;
    Event(FSM *_fsm)
    {
        fsm = _fsm;
    }
protected:
    FSM* fsm = nullptr;
};
#endif // FSM_H
