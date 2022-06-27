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
    enum Options {
        Option_Invalid,
        Register,
        Login,
        Change_username,
        Change_password,
        Change_email

        //others...
    };

    Options resolveOption(std::string input) {
        static const std::map<std::string, Options> optionStrings{
            { "/login", Login },
            { "/register", Register },
            { "/change_username", Change_username },
            { "/change_password", Change_password },
            { "/change_email", Change_email },
        };

        auto itr = optionStrings.find(input);
        if (itr != optionStrings.end()) {
            return itr->second;
        }
        return Option_Invalid;
    }
};
