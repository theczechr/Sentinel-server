#pragma once
#include "account.hpp"
#include "database.hpp"

#include <drogon/WebSocketController.h>

class WebSocketAccount : public drogon::WebSocketController<WebSocketAccount>
{
public:
    virtual void handleNewMessage(const drogon::WebSocketConnectionPtr&, std::string&&, const drogon::WebSocketMessageType&) override;
    virtual void handleConnectionClosed(const drogon::WebSocketConnectionPtr&) override;
    virtual void handleNewConnection(const drogon::HttpRequestPtr&, const drogon::WebSocketConnectionPtr&) override;

    WS_PATH_LIST_BEGIN
    WS_PATH_ADD("/register", drogon::Head);
    WS_PATH_ADD("/login", drogon::Head);
    WS_PATH_ADD("/changeUsername", drogon::Head);
    WS_PATH_ADD("/changeEmail", drogon::Head);
    WS_PATH_ADD("/changePassword", drogon::Head);
    WS_PATH_LIST_END
private:
};

Account account;