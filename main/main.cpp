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
    auto& s = conn->getContextRef<Subscriber>();
    chatRooms_.unsubscribe(s.chatRoomName_, s.id_);
}

void WebSocketChat::handleNewConnection(const drogon::HttpRequestPtr& req, const drogon::WebSocketConnectionPtr& conn)
{
    //LOG_INFO << req->getPath();

    LOG_DEBUG << "New websocket connection!";
    //auto res = drogon::HttpResponsePtr();
    //Subscriber s;
    //s.chatRoomName_ = req->getParameter("room_name");
    //s.id_ = chatRooms_.subscribe(s.chatRoomName_, [conn](const std::string& topic, const std::string& message)
    //{
    //    // Supress unused variable warning
    //    (void)topic;
    //    conn->send(message);
    //});
    //conn->setContext(std::make_shared<Subscriber>(std::move(s)));
    if (req->getPath() == "/register")
    {
        LOG_INFO << "Header 'username': " << req->getParameter("username");
        LOG_INFO << "Header 'email_hash': " << req->getParameter("email_hash");
        LOG_INFO << "Header 'password_hash': " << req->getParameter("password_hash");
        LOG_INFO << "Header 'phone_hash': " << req->getParameter("phone_hash");
        LOG_INFO << "Request path '" << req->getPath() << "'";
    }
    else if (req->getPath() == "/login")
    {
        LOG_INFO << "Header 'username': " << req->getParameter("username");
        LOG_INFO << "Header 'password_hash': " << req->getParameter("password_hash");
        LOG_INFO << "Request path '" << req->getPath() << "'";
    }
}

int main()
{
    drogon::app().addListener("127.0.0.1", 8848).run();
}

//#include <trantor/utils/Logger.h>
//#include <SQLiteCpp/SQLiteCpp.h>
//#include "database.hpp"
//
//int main()
//{
//    database::create();
//    database::create_account("karlos", "Dh3HMLVDEd", "ScSATQ7Efy", "GrceO7gb3G", "co jak kdy kde");
//    database::create_account("robin", "kbwAMK6nDQ", "pAkd7h1Z5r", "cLdR9OH9jY", "na proc o vim");
//    database::display();
//    database::user_exist_full("karlos", "Dh3HMLVDEd", "ScSATQ7Efy", "GrceO7gb3G");
//    database::update_user("phone_hash", "GrceO7gb3G", "fungujeTo");
//    database::display();
//}
