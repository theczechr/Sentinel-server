#include <drogon/HttpAppFramework.h>
#include <Database.hpp>
#include <Tables.hpp>

int main()
{
    //drogon::app().addListener("127.0.0.1", 8848).run();

    Database db;
    Table Accounts(db, "Accounts", { {"uuid", "TEXT NOT NULL"}, {"username", "TEXT NOT NULL"}, {"recovery_phrase", "TEXT"}, {"status", "INTEGER"}, {"last_login", "INTEGER NOT NULL"}});
    Accounts.add_items(db, { "fygd","sdfgfgh","fdg34 hgfd", "1", "453543" });
    LOG_INFO << Accounts.item_exist(db, "uuid", "fygd");
}