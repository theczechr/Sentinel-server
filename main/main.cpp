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
    //LOG_INFO << "SQlite3 version " << SQLite::VERSION << " (" << SQLite::getLibVersion() << ")";
    //LOG_INFO << "SQliteC++ version " << SQLITECPP_VERSION;

    //try
    //{
    //    // Open a database file in create/write mode
    //    SQLite::Database db(db_name, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    //    LOG_INFO << "SQLite database file '" << db.getFilename().c_str() << "' opened successfully";

    //    // Create a new table with an explicit "id" column aliasing the underlying rowid
    //    db.exec("DROP TABLE IF EXISTS " + tb_name);
    //    db.exec("CREATE TABLE " + tb_name + " (username USERNAME, email_hash EMAIL_HASH, password_hash PASSWORD_HASH, phone_hash PHONE_HASH, recovery_phrase RECOVERY_PHRASE)");

    //    // first row
    //    db.exec("INSERT INTO " + tb_name + " VALUES (NULL, NULL, NULL, NULL, NULL)");
    //    db.exec("UPDATE " + tb_name + " SET username = \"sdffsfd\", email_hash = \"sjahdea53421u123fsfds\", password_hash = \"sjahde2wdf21u123fsfds\", phone_hash = \"y2189hdgf43iohfsdfhfd21\", recovery_phrase = \"co delas dneska\"");

    //    // Check the results : expect two row of result
    //    SQLite::Statement query(db, "SELECT * FROM " + tb_name);
    //    LOG_INFO << "SELECT * FROM " + tb_name + " :";
    //    while (query.executeStep())
    //    {
    //        std::cout << "row (" << query.getColumn(0) << ", \"" << query.getColumn(1) << ", \"" << query.getColumn(2) << ", \"" << query.getColumn(3) << ", \"" << query.getColumn(4) << ", \"" << query.getColumn(5) << "\")\n";
    //    }
    //}
    //catch (std::exception& e)
    //{
    //    LOG_INFO << "SQLite exception: " << e.what();
    //    return EXIT_FAILURE; // unexpected error
    //}

    //LOG_INFO << "everything ok, quitting";

    //return EXIT_SUCCESS;

    database::create();
    database::create_account("fdsufg", "sjahdeawdfhsu123fsfds", "sjahde2wdfhsu123fsfds", "y2189hdgfsuiohfsdfhfd21", "ahoj jak se mas dneska");
    //database::create_account("as2fda", "sjahdeaw22hsu123fsfds", "sjahd12wdfhsu123fsfds", "y2189hdgfsugfhfsdfhfd21", "ahoj cof se mas dneska");
    database::display();
    std::cout << "dsada" << database::get("email_hash") << std::endl;
}
