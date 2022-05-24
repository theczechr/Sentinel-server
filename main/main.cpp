////#include "../vendor/aixlog.hpp"
////
////#include "menu.hpp"
////
////int main()
////{
////	menu::start();
////}
//#include <drogon/WebSocketController.h>
//#include <drogon/PubSubService.h>
//#include <drogon/HttpAppFramework.h>
//
//class WebSocketChat : public drogon::WebSocketController<WebSocketChat>
//{
//public:
//    virtual void handleNewMessage(const drogon::WebSocketConnectionPtr&, std::string&&, const drogon::WebSocketMessageType&) override;
//    virtual void handleConnectionClosed(const drogon::WebSocketConnectionPtr&) override;
//    virtual void handleNewConnection(const drogon::HttpRequestPtr&, const drogon::WebSocketConnectionPtr&) override;
//    WS_PATH_LIST_BEGIN
//    WS_PATH_ADD("/ping", drogon::Get);
//    WS_PATH_LIST_END
//private:
//    drogon::PubSubService<std::string> chatRooms_;
//};
//
//struct Subscriber
//{
//    std::string chatRoomName_;
//    drogon::SubscriberID id_;
//};
//
//void WebSocketChat::handleNewMessage(const drogon::WebSocketConnectionPtr& wsConnPtr, std::string&& message, const drogon::WebSocketMessageType& type)
//{
//    if (type == drogon::WebSocketMessageType::Ping)
//    {
//        LOG_DEBUG << "Received a ping from: " << wsConnPtr->peerAddr().toIpPort();
//    }
//    else if (type == drogon::WebSocketMessageType::Text)
//    {
//        auto& s = wsConnPtr->getContextRef<Subscriber>();
//        chatRooms_.publish(s.chatRoomName_, message);
//        LOG_DEBUG << "Received a message from: " << wsConnPtr->peerAddr().toIpPort() << ": " << message;
//    }
//}
//
//void WebSocketChat::handleConnectionClosed(const drogon::WebSocketConnectionPtr& conn)
//{
//    LOG_DEBUG << "Websocket closed!";
//    auto& s = conn->getContextRef<Subscriber>();
//    chatRooms_.unsubscribe(s.chatRoomName_, s.id_);
//}
//
//void WebSocketChat::handleNewConnection(const drogon::HttpRequestPtr& req, const drogon::WebSocketConnectionPtr& conn)
//{
//    LOG_DEBUG << "New websocket connection!";
//    Subscriber s;
//    s.chatRoomName_ = req->getParameter("room_name");
//    s.id_ = chatRooms_.subscribe(s.chatRoomName_, [conn](const std::string& topic, const std::string& message)
//    {
//        // Supress unused variable warning
//        (void)topic;
//        conn->send(message);
//    });
//    conn->setContext(std::make_shared<Subscriber>(std::move(s)));
//}
//
//int main()
//{
//    drogon::app().addListener("127.0.0.1", 8848).run();
//}

#include <trantor/utils/Logger.h>
#include <SQLiteCpp/SQLiteCpp.h>
#include "database.hpp"

int main()
{
    database::create();
    database::create_account("fdsufg", "sjahdeawdfhsu123fsfds", "sjahde2wdfhsu123fsfds", "y2189hdgfsuiohfsdfhfd21", "ahoj jak se mas dneska");
    //database::create_account("as2fda", "sjahdeaw22hsu123fsfds", "sjahd12wdfhsu123fsfds", "y2189hdgfsugfhfsdfhfd21", "ahoj cof se mas dneska");
    database::display();
    database::user_exist("dd", "sjahdeawdfhsu123fsfds", "sjahde2wdfhsu123fsfds", "y2189hdgfsuiohfsdfhfd21");
}
