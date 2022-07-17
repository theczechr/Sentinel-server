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

void database::display_accounts()
{
	LOG_INFO << "SQlite3 version " << SQLite::VERSION << " (" << SQLite::getLibVersion() << ")";
	LOG_INFO << "SQliteC++ version " << SQLITECPP_VERSION;
	LOG_INFO << "Displaying all accounts";

	if (!utils::file_exist(db_name))
	{
		LOG_ERROR << "SQLite database file '" << db_name << "' doesn't exist, quitting";
		return;
	}

	SQLite::Database db(db_name, SQLite::OPEN_READWRITE);

	SQLite::Statement query(db, "SELECT * FROM Accounts");
	while (query.executeStep())
	{
		std::cout << "row (" << query.getColumn(0) << ", \"" << query.getColumn(1) << query.getColumn(2) << ", \"" << query.getColumn(3) << ", \"" << query.getColumn(4) << "\")\n";
	}
	
	LOG_INFO << "Successfully displayed all accounts, quitting";
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
	db.exec("INSERT INTO Accounts VALUES('" + uuid + "','" + public_key + "','" + username + "','" + recovery_phrase + "','" + std::to_string(last_login) + "')");

	LOG_INFO << "Account with uuid '" << uuid << "' created, quitting";
}

bool database::recovery_login(std::string username, std::string recovery_phrase, long last_login)
{
	if (!utils::file_exist(db_name))
	{
		LOG_ERROR << "SQLite database file '" << db_name << "' doesn't exist, quitting";
		return false;
	}
	SQLite::Database db(db_name, SQLite::OPEN_READWRITE);

	SQLite::Statement query(db, "SELECT EXISTS(SELECT 1 FROM Accounts WHERE username = '" + username + "' AND recovery_phrase = '" + recovery_phrase + "')");
	while (query.executeStep())
	{
		if (!query.getColumn(0).getInt())
		{
			return false;
		}
	}
	db.exec("UPDATE Accounts SET last_login = '" + std::to_string(last_login) + "'" + " WHERE username = '" + username + "' AND recovery_phrase = '" + recovery_phrase + "'");
	return true;

}
