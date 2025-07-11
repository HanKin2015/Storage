// event_client.h - 客户端实现

#ifndef EVENT_CLIENT_H
#define EVENT_CLIENT_H

#include "event_socket.h"
#include <string>

class EventClient : public EventSocket {
public:
    EventClient(const std::string& socketPath);
    
protected:
    bool setupSocket() override;

private:
    std::string m_socketPath;
};

#endif // EVENT_CLIENT_H