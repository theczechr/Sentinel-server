#include "database.hpp"

std::string db_name = "KRappDB.db3";
std::string tb_name = "users";

void database::create()
{
    LOG_INFO << "SQlite3 version " << SQLite::VERSION << " (" << SQLite::getLibVersion() << ")";
    LOG_INFO << "SQliteC++ version " << SQLITECPP_VERSION;
    LOG_INFO << "Creating new database: " << db_name;

    if (utils::file_exist(db_name))
        LOG_ERROR << "Database file already exist!";
	else
	{
		try
		{
			SQLite::Database db(db_name, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
			LOG_INFO << "Database file created successfully";
			db.exec("CREATE TABLE " + tb_name + " (username USERNAME, email_hash EMAIL_HASH, password_hash PASSWORD_HASH, phone_hash PHONE_HASH, recovery_phrase RECOVERY_PHRASE)");
			LOG_INFO << "Inserting NULL values";
			db.exec("INSERT INTO " + tb_name + " VALUES (NULL, NULL, NULL, NULL, NULL)");
		}
		catch (std::exception& e)
		{
		    LOG_ERROR << "SQLite exception: " << e.what();
		    return;
		}
		LOG_INFO << "Database created successfully, quitting";
	}
}

void database::display()
{
	LOG_INFO << "Reading database";
	SQLite::Database db(db_name, SQLite::OPEN_READONLY);
	LOG_INFO << "SQLite database file '" << db_name << "' opened successfully";

	try
	{
		SQLite::Statement query(db, "SELECT * FROM " + tb_name);
		LOG_INFO << tb_name << ":";
		while (query.executeStep())
		{
			std::cout << "Row (" << query.getColumn(0) << ", \"" << query.getColumn(1) << ", \"" << query.getColumn(2) << ", \"" << query.getColumn(3) << ", \"" << query.getColumn(4) << "\")\n";
		}
	}
	catch (std::exception& e)
	{
		LOG_ERROR << "SQLite exception: " << e.what();
		return;
	}
	LOG_INFO << "Quitting";
}

void database::create_account(std::string username, std::string email_hash, std::string password_hash, std::string phone_hash, std::string recovery_phrase)
{
	LOG_INFO << "Creating new account";
	SQLite::Database db(db_name, SQLite::OPEN_READWRITE);
	LOG_INFO << "SQLite database file '" << db_name << "' opened successfully";
	
	try
	{
		db.exec("INSERT INTO " + tb_name + " VALUES (\"" + username + "\", \"" + email_hash + "\", \"" + password_hash + "\", \"" + phone_hash + "\", \"" + recovery_phrase + "\")");
		
	}
	catch (std::exception& e)
	{
		LOG_ERROR << "SQLite exception: " << e.what();
		return;
	}
	LOG_INFO << "Account created successfully, quitting";
}

bool database::user_exist(std::string username, std::string email_hash, std::string password_hash, std::string phone_hash)
{
	LOG_INFO << "Finding in database";
	SQLite::Database db(db_name, SQLite::OPEN_READONLY);
	LOG_INFO << "SQLite database file '" << db_name << "' opened successfully";

	SQLite::Statement query(db, "SELECT EXISTS(SELECT 1 FROM users WHERE username = \"" + username + "\")");
	while (query.executeStep())
	{
		std::cout << "query.getColumn(0): " << query.getColumn(0); // 0 - false, 1 - true
	}
	return true;
}