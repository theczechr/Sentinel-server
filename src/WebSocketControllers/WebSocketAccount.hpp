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
	WS_PATH_ADD("/changePkf", drogon::Head);
	WS_PATH_ADD("/changeRecoveryPhrase", drogon::Head);
	WS_PATH_ADD("/recovery", drogon::Head);
	WS_PATH_ADD("/deactivate", drogon::Head);
	WS_PATH_LIST_END
private:
	AccountManager account_manager;

	enum Options {
		Option_Invalid,
		Register,
		Login,
		Change_username,
		Change_pkf,
		Change_recovery_phrase,
		Recovery,
		Deactivate
		//others...
	};

	Options resolveOption(std::string input) {
		static const std::map<std::string, Options> optionStrings{
			{ "/register", Register },
			{ "/login", Login },
			{ "/changeUsername", Change_username },
			{ "/changePkf", Change_pkf },
			{ "/changeRecoveryPhrase", Change_recovery_phrase },
			{ "/recovery", Recovery },
			{ "/deactivate", Deactivate }
		};

		std::map<std::string, WebSocketAccount::Options>::const_iterator itr = optionStrings.find(input);
		if (itr != optionStrings.end()) {
			return itr->second;
		}
		return Option_Invalid;
	}
};