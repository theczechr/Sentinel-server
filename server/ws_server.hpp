#pragma once
#include <drogon/WebSocketController.h>
#include <drogon/PubSubService.h>
#include <drogon/HttpAppFramework.h>


class WebSocketChat : public drogon::WebSocketController<WebSocketChat>
{
public:
    virtual void handleNewMessage(const drogon::WebSocketConnectionPtr&, std::string&&, const drogon::WebSocketMessageType&) override;
    virtual void handleConnectionClosed(const drogon::WebSocketConnectionPtr&) override;
    virtual void handleNewConnection(const drogon::HttpRequestPtr&, const drogon::WebSocketConnectionPtr&) override;
    WS_PATH_LIST_BEGIN
        WS_PATH_ADD("/connectionTest", drogon::Get);
    WS_PATH_ADD("/register", drogon::Head);
    WS_PATH_ADD("/login", drogon::Head);
    WS_PATH_LIST_END
private:
    drogon::PubSubService<std::string> chatRooms_;
};

struct Subscriber
{
    std::string chatRoomName_;
    drogon::SubscriberID id_;
};