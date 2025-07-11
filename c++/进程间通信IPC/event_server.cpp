// event_server.cpp - 服务器实现

#include "event_server.h"
#include <sys/un.h>
#include <iostream>

EventServer::EventServer(const std::string& socketPath)
    : m_socketPath(socketPath), m_listener(nullptr) {}

EventServer::~EventServer() {
    if (m_listener) {
        evconnlistener_free(m_listener);
    }
}

bool EventServer::setupSocket() {
    // 设置Unix域套接字地址
    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, m_socketPath.c_str(), sizeof(addr.sun_path) - 1);
    
    // 移除已存在的套接字文件
    unlink(m_socketPath.c_str());
    
    // 创建监听器
    m_listener = evconnlistener_new_bind(
        m_eventBase, 
        acceptCallback, 
        this,
        LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE,
        -1, 
        (struct sockaddr*)&addr, 
        sizeof(addr)
    );
    
    if (!m_listener) {
        std::cerr << "Failed to create listener on: " << m_socketPath << std::endl;
        return false;
    }
    
    // 设置错误回调
    evconnlistener_set_error_cb(m_listener, errorCallback);
    
    return true;
}

void EventServer::onConnected() {
    // 服务器端不需要实现这个方法，因为连接是由监听器处理的
}

void EventServer::acceptCallback(struct evconnlistener* listener, 
                                evutil_socket_t fd, 
                                struct sockaddr* address, 
                                int socklen, 
                                void* ctx) {
    EventServer* server = static_cast<EventServer*>(ctx);
    
    // 创建新的bufferevent处理这个连接
    struct bufferevent* bev = bufferevent_socket_new(
        event_base_new(), 
        fd, 
        BEV_OPT_CLOSE_ON_FREE
    );
    
    // 设置回调函数
    bufferevent_setcb(bev, 
        [](struct bufferevent* bev, void* ctx) {
            EventServer* self = static_cast<EventServer*>(ctx);
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
            if (events & (BEV_EVENT_EOF | BEV_EVENT_ERROR)) {
                bufferevent_free(bev);
            }
        },
        server
    );
    
    // 启用读写事件
    bufferevent_enable(bev, EV_READ | EV_WRITE);
    
    std::cout << "New client connected" << std::endl;
}

void EventServer::errorCallback(struct evconnlistener* listener, void* ctx) {
    struct event_base* base = evconnlistener_get_base(listener);
    int err = EVUTIL_SOCKET_ERROR();
    std::cerr << "Listener error " << err << ": " << evutil_socket_error_to_string(err) << std::endl;
    event_base_loopexit(base, nullptr);
}