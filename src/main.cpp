#include "Account/AccountManager.hpp"
#include <drogon/HttpAppFramework.h>
#include <jsoncpp/json/json.h>

int main() {
	drogon::app().addListener("127.0.0.1", 8848).run();
}
