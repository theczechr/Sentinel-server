#include <drogon/HttpAppFramework.h>
#include "AccountManager.hpp"

int main()
{
	drogon::app().addListener("127.0.0.1", 8848).run();

	//Utils::UUID uuid;

	//// Public key fingerprint
	//std::string pbf1 = "43:51:43:a1:b5:fc:8b:b7:0a:3a:a9:b1:0f:66:73:a8";
	//std::string pbf2 = "43:51:43:a1:b5:fc:8b:b7:0a:3a:a9:b1:0f:66:73:a8";
	//std::string pbf3 = "43:51:43:a1:b5:fc:8b:b7:0a:3a:a9:b1:0f:66:73:a8";

	//// Username
	//std::string username1 = "fdfdr";
	//std::string username2 = "gfjhg";
	//std::string username3 = "Test";

	//// Recovery phrase
	//std::string rp1 = "jedna dva";
	//std::string rp2 = "tri ctyri";
	//std::string rp3 = "pet sest";

	////at.create_account(pbf1, username1, rp1, unix_ts);
	////at.create_account(pbf2, username2, rp2, unix_ts);
	////at.create_account(pbf3, username3, rp3, unix_ts);

	////Account a1;
	////Account a2;
	////Account a3;
	////AccountManager am1(a1);
	////AccountManager am2(a2);
	////AccountManager am3(a3);

	//Utils::UUID uuid1 = uuid.generage_new();
	//Utils::UUID uuid2 = uuid.generage_new();

	//am1.create(uuid1, username1, pbf1, rp1);
	//am2.create(uuid2, username2, pbf2, rp2);

	//Account a1t = am1.get_by_uuid(uuid1);
	//am1.update_username(a1t, "this is a test username");
	//LOG_INFO << "a1t username: '" << a1t.get_username() << "'";
	//
	// UUID nemuzu accessnout (bude se to posilat z clientu)
	// Jinak bych mohl jedno z toho

	//at.create_account()
	//Table Accounts(db, "Accounts", { {"uuid", "TEXT NOT NULL"}, {"username", "TEXT NOT NULL"}, {"recovery_phrase", "TEXT"}, {"status", "INTEGER"}, {"last_login", "INTEGER NOT NULL"}});
	//Accounts.add_row({ "fygd","sdfgfgh","fdg34 hgfd", "1", "453543" });
	//LOG_INFO << Accounts.value_exist("uuid", "fygd");
	//Accounts.update_value_where(db, "status", "0", "uuid", "fygd");
	//Accounts.delete_rows_where("status", "0");
}