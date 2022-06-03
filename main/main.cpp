#include "ws_server.hpp"

int main()
{
    drogon::app().addListener("127.0.0.1", 8848).run();
}