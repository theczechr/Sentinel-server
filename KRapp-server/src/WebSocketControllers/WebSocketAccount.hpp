#pragma once
#include "AccountManager.hpp"

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
	WS_PATH_ADD("/recovery", drogon::Head);
	WS_PATH_LIST_END
private:
	AccountManager account_manager;

	enum Options {
		option_Invalid,
		Register,
		login,
		change_username,
		recovery
		//others...
	};

	Options resolveOption(std::string input) {
		static const std::map<std::string, Options> optionStrings{
			{ "/register", Register },
			{ "/login", login },
			{ "/changeUsername", change_username },
			{ "/recovery", recovery },
		};

		auto itr = optionStrings.find(input);
		if (itr != optionStrings.end()) {
			return itr->second;
		}
		return option_Invalid;
	}
};