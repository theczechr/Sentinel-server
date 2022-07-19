#include <drogon/HttpAppFramework.h>
#include <Database.hpp>
#include <Tables.hpp>

int main()
{
    //drogon::app().addListener("127.0.0.1", 8848).run();
    Database db;
    Table table(db, "Accounts", { {"uuid", "TEXT NOT NULL"}, {"username", "TEXT NOT NULL"}, {"recovery_phrase", "TEXT"}, {"status", "INTEGER"}, {"last_login", "INTEGER NOT NULL"}});
    //database::create();
    //database::create_tables();
    //database::create_account("sdhgasdjd", "pub1key", "testo", "sdad sjdkadj sdaha yhgb", 123651321);
    //std::cout << database::recovery_login("testo", "sdad sjdkadj sdaha yhgb", 347289);
}