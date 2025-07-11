// event_socket.cpp - 基类实现

#include "event_socket.h"
#include <iostream>

EventSocket::EventSocket()
    : m_eventBase(nullptr), m_bufferEvent(nullptr), m_isConnected(false) {}

EventSocket::~EventSocket() {
    stop();
}

bool EventSocket::start() {
    // 创建事件库实例
    m_eventBase = event_base_new();
    if (!m_eventBase) {
        std::cerr << "Failed to create event base" << std::endl;
        return false;
    }

    // 创建并配置bufferevent
    m_bufferEvent = bufferevent_socket_new(m_eventBase, -1, BEV_OPT_CLOSE_ON_FREE);
    if (!m_bufferEvent) {
        std::cerr << "Failed to create bufferevent" << std::endl;
        event_base_free(m_eventBase);
        m_eventBase = nullptr;
        return false;
    }

    // 设置回调函数
    bufferevent_setcb(m_bufferEvent, 
        [](struct bufferevent* bev, void* ctx) {
            EventSocket* self = static_cast<EventSocket*>(ctx);
            struct evbuffer* input = bufferevent_get_input(bev);
            size_t len = evbuffer_get_length(input);
            
            if (len > 0) {
                char buffer[4096];
                size_t read = evbuffer_remove(input, buffer, sizeof(buffer) - 1);
                buffer[read] = '\0';
                
                if (self->m_messageCallback) {
                    self->m_messageCallback(std::string(buffer, read));
                }
            }
        },
        nullptr,
        [](struct bufferevent* bev, short events, void* ctx) {
            EventSocket* self = static_cast<EventSocket*>(ctx);
            
            if (events & BEV_EVENT_CONNECTED) {
                self->m_isConnected = true;
                self->onConnected();
                if (self->m_connectionCallback) {
                    self->m_connectionCallback(true);
                }
            } else if (events & (BEV_EVENT_EOF | BEV_EVENT_ERROR)) {
                self->m_isConnected = false;
                self->onDisconnected();
                if (self->m_connectionCallback) {
                    self->m_connectionCallback(false);
                }
                // 连接断开后，清理bufferevent
                bufferevent_free(self->m_bufferEvent);
                self->m_bufferEvent = nullptr;
            }
        },
        this
    );

    // 启用读写事件
    bufferevent_enable(m_bufferEvent, EV_READ | EV_WRITE);

    // 调用子类的套接字设置方法
    if (!setupSocket()) {
        std::cerr << "Failed to setup socket" << std::endl;
        bufferevent_free(m_bufferEvent);
        event_base_free(m_eventBase);
        m_bufferEvent = nullptr;
        m_eventBase = nullptr;
        return false;
    }

    // 启动事件循环（在单独线程中运行）
    std::thread([this]() {
        event_base_dispatch(m_eventBase);
    }).detach();

    return true;
}

void EventSocket::stop() {
    if (m_eventBase) {
        event_base_loopbreak(m_eventBase);
        event_base_free(m_eventBase);
        m_eventBase = nullptr;
    }
    
    if (m_bufferEvent) {
        bufferevent_free(m_bufferEvent);
        m_bufferEvent = nullptr;
    }
    
    m_isConnected = false;
}

bool EventSocket::sendMessage(const std::string& message) {
    if (!m_isConnected || !m_bufferEvent) {
        std::cerr << "Not connected, cannot send message" << std::endl;
        return false;
    }
    
    struct evbuffer* output = bufferevent_get_output(m_bufferEvent);
    evbuffer_add(output, message.c_str(), message.length());
    return true;
}

void EventSocket::setMessageCallback(const MessageCallback& callback) {
    m_messageCallback = callback;
}

void EventSocket::setConnectionCallback(const ConnectionCallback& callback) {
    m_connectionCallback = callback;
}

void EventSocket::onConnected() {
    std::cout << "Connection established" << std::endl;
}

void EventSocket::onDisconnected() {
    std::cout << "Connection disconnected" << std::endl;
}