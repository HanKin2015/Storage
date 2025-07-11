// event_server.h - 服务器实现

#ifndef EVENT_SERVER_H
#define EVENT_SERVER_H

#include "event_socket.h"
#include <string>
#include <event2/listener.h>

class EventServer : public EventSocket {
public:
    EventServer(const std::string& socketPath);
    ~EventServer();
    
protected:
    bool setupSocket() override;
    void onConnected() override;

private:
    std::string m_socketPath;
    struct evconnlistener* m_listener;
    
    // 监听器回调
    static void acceptCallback(struct evconnlistener* listener, 
                              evutil_socket_t fd, 
                              struct sockaddr* address, 
                              int socklen, 
                              void* ctx);
    
    // 错误回调
    static void errorCallback(struct evconnlistener* listener, void* ctx);
};

#endif // EVENT_SERVER_H