#include <drogon/HttpAppFramework.h>
#include "AccountsTable.hpp"
#include "UNIX_TS.hpp"

int main()
{
    //drogon::app().addListener("127.0.0.1", 8848).run();

    AccountsTable at;
    Core::UNIX_TS last_login;

    // Public key fingerprint
    std::string pbf1 = "43:51:43:a1:b5:fc:8b:b7:0a:3a:a9:b1:0f:66:73:a8";
    std::string pbf2 = "43:51:43:a1:b5:fc:8b:b7:0a:3a:a9:b1:0f:66:73:a8";
    std::string pbf3 = "43:51:43:a1:b5:fc:8b:b7:0a:3a:a9:b1:0f:66:73:a8";
    
    // Username
    std::string username1 = "Karlos";
    std::string username2 = "Robis";
    std::string username3 = "Test";

    // Recovery phrase
    std::string rp1 = "jedna dva";
    std::string rp2 = "tri ctyri";
    std::string rp3 = "pet sest";

    at.create_account(pbf1, username1, rp1, last_login);
    at.create_account(pbf2, username2, rp2, last_login);
    at.create_account(pbf3, username3, rp3, last_login);

    // UUID nemuzu accessnout (bude se to posilat z clientu)
    // Jinak bych mohl jedno z toho

    //at.create_account()
    //Table Accounts(db, "Accounts", { {"uuid", "TEXT NOT NULL"}, {"username", "TEXT NOT NULL"}, {"recovery_phrase", "TEXT"}, {"status", "INTEGER"}, {"last_login", "INTEGER NOT NULL"}});
    //Accounts.add_row({ "fygd","sdfgfgh","fdg34 hgfd", "1", "453543" });
    //LOG_INFO << Accounts.value_exist("uuid", "fygd");
    //Accounts.update_value_where(db, "status", "0", "uuid", "fygd");
    //Accounts.delete_rows_where("status", "0");
}