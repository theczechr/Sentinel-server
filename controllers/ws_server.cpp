#include "ws_server.hpp"

void WebSocketChat::handleNewMessage(const drogon::WebSocketConnectionPtr& wsConnPtr, std::string&& message, const drogon::WebSocketMessageType& type)
{
    if (type == drogon::WebSocketMessageType::Ping)
    {
        LOG_DEBUG << "Received a ping from: " << wsConnPtr->peerAddr().toIpPort();
    }
    else if (type == drogon::WebSocketMessageType::Text)
    {
        auto& s = wsConnPtr->getContextRef<Subscriber>();
        chatRooms_.publish(s.chatRoomName_, message);
        LOG_DEBUG << "Received a message from: " << wsConnPtr->peerAddr().toIpPort() << ": " << message;
    }
    LOG_INFO << "Connection from '" << wsConnPtr->peerAddr().toIpPort() << "' | message '" << message << "'";
}

void WebSocketChat::handleConnectionClosed(const drogon::WebSocketConnectionPtr& conn)
{
    LOG_DEBUG << "Websocket closed!";
    //auto& s = conn->getContextRef<Subscriber>();
    //chatRooms_.unsubscribe(s.chatRoomName_, s.id_);
}

void WebSocketChat::handleNewConnection(const drogon::HttpRequestPtr& req, const drogon::WebSocketConnectionPtr& conn)
{
    LOG_DEBUG << "New websocket connection!";
    //auto res = drogon::HttpResponsePtr();
    //Subscriber s;
    //s.chatRoomName_ = req->getParameter("room_name");
    //s.id_ = chatRooms_.subscribe(s.chatRoomName_, [conn](const std::string& topic, const std::string& message)
    //    {
    //        // Supress unused variable warning
    //        (void)topic;
    //        conn->send(message);
    //    });
    //conn->setContext(std::make_shared<Subscriber>(std::move(s)));
    std::string a = "asdsad";
    if (req->getPath() == "/register")
    {
        LOG_INFO << "Request path '" << req->getPath() << "'";

        if (database::user_exist_full(req->getParameter("username"), req->getParameter("email_hash"), req->getParameter("password_hash"), req->getParameter("phone_hash")))
        {
            conn->send("1", drogon::WebSocketMessageType::Binary);
            return;
        }
        database::create_account(req->getParameter("username"), req->getParameter("email_hash"), req->getParameter("password_hash"), req->getParameter("phone_hash"), "co jak kdy kde");
        conn->send("Successfully registered.");

    }
    else if (req->getPath() == "/login")
    {
        LOG_INFO << "Header 'username': " << req->getParameter("username");
        LOG_INFO << "Header 'password_hash': " << req->getParameter("password_hash");
        LOG_INFO << "Request path '" << req->getPath() << "'";
    }
}