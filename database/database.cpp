#include "database.hpp"

std::string db_name = "krapp.db";

void database::create()
{
    LOG_INFO << "SQlite3 version " << SQLite::VERSION << " (" << SQLite::getLibVersion() << ")";
    LOG_INFO << "SQliteC++ version " << SQLITECPP_VERSION;
    LOG_INFO << "Creating new database file '" << db_name << "'";

	if (utils::file_exist(db_name))
	{
		LOG_ERROR << "SQLite database file '" << db_name << "' already exist, quitting";
		return;
	}

	SQLite::Database db(db_name, SQLite::OPEN_CREATE | SQLite::OPEN_READWRITE);
	LOG_INFO << "SQLite database file '" << db_name << "' created successfully. quitting";
}

void database::exec(std::string command)
{
	LOG_INFO << "SQlite3 version " << SQLite::VERSION << " (" << SQLite::getLibVersion() << ")";
	LOG_INFO << "SQliteC++ version " << SQLITECPP_VERSION;
	LOG_INFO << "Executing command into '" << db_name << "'";

	if (!utils::file_exist(db_name))
	{
		LOG_ERROR << "SQLite database file '" << db_name << "' doesn't exist, quitting";
		return;
	}

	SQLite::Database db(db_name, SQLite::OPEN_READWRITE);
	db.exec(command);

	LOG_INFO << "Command executed, quitting";
}

void database::create_tables()
{
	LOG_INFO << "SQlite3 version " << SQLite::VERSION << " (" << SQLite::getLibVersion() << ")";
	LOG_INFO << "SQliteC++ version " << SQLITECPP_VERSION;
	LOG_INFO << "Creating database tables in database file '" << db_name << "'";

	if (!utils::file_exist(db_name))
	{
		LOG_ERROR << "SQLite database file '" << db_name << "' doesn't exist, quitting";
		return;
	}

	SQLite::Database db(db_name, SQLite::OPEN_READWRITE);

	// Accounts table
	db.exec("CREATE TABLE \"Accounts\" (\"uuid\"	TEXT NOT NULL UNIQUE, \"public_key\"	TEXT NOT NULL UNIQUE, \"username\"	TEXT NOT NULL, \"recovery_phrase\" TEXT, \"last_login\"	INTEGER NOT NULL)");
	// ...

	LOG_INFO << "Tables created, quitting";
}

void database::create_account(std::string uuid, std::string public_key, std::string username, std::string recovery_phrase, long last_login)
{
	LOG_INFO << "Creating new account with uuid '" << uuid << "'";

	if (!utils::file_exist(db_name))
	{
		LOG_ERROR << "SQLite database file '" << db_name << "' doesn't exist, quitting";
		return;
	}
	SQLite::Database db(db_name, SQLite::OPEN_READWRITE);
	//db.exec("INSERT INTO accounts VALUES(" + uuid + "," + public_key + "," + username + "," + recovery_phrase + "," + std::to_string(last_login) + ")"); // Error ?

	LOG_INFO << "Account with uuid '" << uuid << "' created, quitting";
}
