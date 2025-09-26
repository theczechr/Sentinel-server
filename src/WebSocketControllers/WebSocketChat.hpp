#pragma once
#include <drogon/PubSubService.h>
#include <drogon/WebSocketController.h>
#include <optional>

class WebSocketChat : public drogon::WebSocketController<WebSocketChat> {
  public:
	virtual void handleNewMessage(const drogon::WebSocketConnectionPtr &, std::string &&, const drogon::WebSocketMessageType &) override;
	virtual void handleConnectionClosed(const drogon::WebSocketConnectionPtr &) override;
	virtual void handleNewConnection(const drogon::HttpRequestPtr &, const drogon::WebSocketConnectionPtr &) override;

	WS_PATH_LIST_BEGIN
	WS_PATH_ADD("/sendtxt", drogon::Head);
	WS_PATH_LIST_END

  private:
	enum Error_codes {
		Wrong_chatroom,
		Unauthorized_access

		// others..
	};
	enum Options {
		Option_Invalid,
		Send_txt,
		Send_media,
		Create_chatroom,
		Delete_chatroom

		// others...
	};

	static constexpr size_t kMaxMessageBytes = 64 * 1024; // 64KB limit

	void foo(const drogon::WebSocketConnectionPtr &conn, Error_codes code) {
		std::string error;

		static const std::map<Error_codes, std::string> errors {
			{Wrong_chatroom, "You tried to message an unexisting user"},
			{Unauthorized_access, "You are not friends with this user"}};

		auto itr = errors.find(code);
		if (itr != errors.end()) {
			error = itr->second;
		} else
			error = "Unknown error";

		conn->send("connection failed, ERROR: " + error);
		conn->forceClose();
	}

	Options resolveOption(std::string input) {
		static const std::map<std::string, Options> optionStrings {{"/sendtxt", Send_txt},
																   {"/sendmedia", Send_media},
																   {"/create_chatroom", Create_chatroom},
																   {"/delete_chatroom", Delete_chatroom}};

		auto itr = optionStrings.find(input);
		if (itr != optionStrings.end()) {
			return itr->second;
		}
		return Option_Invalid;
	}
	drogon::PubSubService<std::string> chatRooms_;
};

struct Subscriber {
	std::string							chatRoomName_;
	std::optional<drogon::SubscriberID> id_;
};
