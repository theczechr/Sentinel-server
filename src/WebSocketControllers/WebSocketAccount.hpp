#pragma once
#include "Account/AccountManager.hpp"

#include <drogon/WebSocketController.h>
#include "Utils/RateLimiter.hpp"

class WebSocketAccount : public drogon::WebSocketController<WebSocketAccount> {
  public:
	virtual void handleNewMessage(const drogon::WebSocketConnectionPtr &, std::string &&, const drogon::WebSocketMessageType &) override;
	virtual void handleConnectionClosed(const drogon::WebSocketConnectionPtr &) override;
	virtual void handleNewConnection(const drogon::HttpRequestPtr &, const drogon::WebSocketConnectionPtr &) override;

	WS_PATH_LIST_BEGIN
	WS_PATH_ADD("/register", drogon::Head);
	WS_PATH_ADD("/login", drogon::Head);
	WS_PATH_ADD("/changeUsername", drogon::Head);
	WS_PATH_ADD("/changePkf", drogon::Head);
	WS_PATH_ADD("/changeRecoveryPhrase", drogon::Head);
	WS_PATH_ADD("/recovery", drogon::Head);
	WS_PATH_ADD("/deactivate", drogon::Head);
	WS_PATH_ADD("/getPubKey", drogon::Head);
	WS_PATH_ADD("/publishPubKey", drogon::Head);
	WS_PATH_LIST_END
  private:
	sentinel::account_manager account_manager;
	sentinel::utils::RateLimiter publish_limiter{5, 60}; // 5 per minute per key

	enum Options {
		Option_Invalid,
		Register,
		Login,
		Change_username,
		Change_pkf,
		Change_recovery_phrase,
		Recovery,
		Deactivate,
		Get_pubkey,
		Publish_pubkey
		// others...
	};

	Options resolveOption(std::string input) {
		static const std::map<std::string, Options> optionStrings {{"/register", Register},
																   {"/login", Login},
																   {"/changeUsername", Change_username},
																   {"/changePkf", Change_pkf},
																   {"/changeRecoveryPhrase", Change_recovery_phrase},
																   {"/recovery", Recovery},
																   {"/deactivate", Deactivate},
																   {"/getPubKey", Get_pubkey},
																   {"/publishPubKey", Publish_pubkey}};

		std::map<std::string, WebSocketAccount::Options>::const_iterator itr = optionStrings.find(input);
		if (itr != optionStrings.end()) {
			return itr->second;
		}
		return Option_Invalid;
	}
};
