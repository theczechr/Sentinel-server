#include <drogon/HttpAppFramework.h>
#include <Database.hpp>
#include <Table.hpp>

int main()
{
    //drogon::app().addListener("127.0.0.1", 8848).run();

    Database db;
    Table Accounts(db, "Accounts", { {"uuid", "TEXT NOT NULL"}, {"username", "TEXT NOT NULL"}, {"recovery_phrase", "TEXT"}, {"status", "INTEGER"}, {"last_login", "INTEGER NOT NULL"}});
    Accounts.add_row({ "fygd","sdfgfgh","fdg34 hgfd", "1", "453543" });
    LOG_INFO << Accounts.value_exist("uuid", "fygd");
    //Accounts.update_value_where(db, "status", "0", "uuid", "fygd");
    Accounts.delete_rows_where("status", "0");
}