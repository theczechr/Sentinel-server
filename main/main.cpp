#include <drogon/HttpAppFramework.h>
#include <database.hpp>

int main()
{
    //drogon::app().addListener("127.0.0.1", 8848).run();
    //database::create();
    //database::create_tables();
    //database::create_account("sdhgasdjd", "pub1key", "testo", "sdad sjdkadj sdaha yhgb", 123651321);
    //std::cout << database::recovery_login("testo", "sdad sjdkadj sdaha yhgb", 347289);
    database::display_accounts();
}