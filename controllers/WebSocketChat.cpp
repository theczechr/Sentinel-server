#include "WebSocketChat.hpp"

void WebSocketChat::handleNewMessage(const drogon::WebSocketConnectionPtr& wsConnPtr, std::string&& message, const drogon::WebSocketMessageType& type)
{
    LOG_DEBUG << "new websocket message:" << message;
    if (type == drogon::WebSocketMessageType::Ping)
    {
        LOG_DEBUG << "recv a ping";
    }
    else if (type == drogon::WebSocketMessageType::Text)
    {
        auto& s = wsConnPtr->getContextRef<Subscriber>();
        chatRooms_.publish(s.chatRoomName_, message);
    }

    LOG_INFO << "Message from '" << wsConnPtr->peerAddr().toIpPort() << "', message content '" << message  << "'";
}

void WebSocketChat::handleConnectionClosed(const drogon::WebSocketConnectionPtr& conn)
{
    LOG_INFO << "Websocket connection closed!";
    auto& s = conn->getContextRef<Subscriber>();
    chatRooms_.unsubscribe(s.chatRoomName_, s.id_);
}

void WebSocketChat::handleNewConnection(const drogon::HttpRequestPtr& req, const drogon::WebSocketConnectionPtr& conn)
{
    LOG_DEBUG << "New websocket connection!";

    conn->send("haha!!!");
    Subscriber s;
    s.chatRoomName_ = req->getParameter("room_name");

    s.id_ = chatRooms_.subscribe(s.chatRoomName_, [conn](const std::string& topic, const std::string& message)
    {
        (void)topic;
        conn->send(message);
    });
    conn->setContext(std::make_shared<Subscriber>(std::move(s)));
}