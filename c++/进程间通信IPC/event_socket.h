// event_socket.h - 基于libevent的套接字抽象基类

#ifndef EVENT_SOCKET_H
#define EVENT_SOCKET_H

#include <string>
#include <functional>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>

class EventSocket {
public:
    // 消息接收回调类型
    using MessageCallback = std::function<void(const std::string&)>;
    // 连接状态回调类型
    using ConnectionCallback = std::function<void(bool)>;

    EventSocket();
    virtual ~EventSocket();

    // 初始化并启动事件循环
    bool start();
    // 停止并清理资源
    void stop();
    // 发送消息
    bool sendMessage(const std::string& message);
    // 设置消息接收回调
    void setMessageCallback(const MessageCallback& callback);
    // 设置连接状态回调
    void setConnectionCallback(const ConnectionCallback& callback);

protected:
    // 子类需实现的方法：创建套接字并连接/监听
    virtual bool setupSocket() = 0;
    // 处理连接建立事件
    virtual void onConnected();
    // 处理连接关闭事件
    virtual void onDisconnected();

    struct event_base* m_eventBase;
    struct bufferevent* m_bufferEvent;
    MessageCallback m_messageCallback;
    ConnectionCallback m_connectionCallback;
    bool m_isConnected;
};

#endif // EVENT_SOCKET_H