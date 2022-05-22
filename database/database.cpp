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

std::string database::get(std::string item)
{
	LOG_INFO << "Getting " << item << " from database";
	SQLite::Database db(db_name, SQLite::OPEN_READONLY);
	LOG_INFO << "SQLite database file '" << db_name << "' opened successfully";

	try
	{
		// udelam to zitra
	}
	catch (std::exception& e)
	{
		LOG_ERROR << "SQLite exception: " << e.what();
		return "";
	}
	LOG_INFO << "Quitting";
}

//
//int main()
//{
//    try
//    {
//        // Open a database file in create/write mode
//        SQLite::Database db("users.db3", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
//        LOG_INFO << "SQLite database file '" << db.getFilename().c_str() << "' opened successfully";
//
//        // Create a new table with an explicit "id" column aliasing the underlying rowid
//        db.exec("DROP TABLE IF EXISTS users");
//        db.exec("CREATE TABLE users (id INTEGER PRIMARY KEY, value TEXT)");
//
//        // first row
//        int nb = db.exec("INSERT INTO test VALUES (NULL, \"test\")");
//        LOG_INFO << "INSERT INTO test VALUES (NULL, \"test\")\", returned " << nb;
//
//        // second row
//        nb = db.exec("INSERT INTO test VALUES (NULL, \"second\")");
//        LOG_INFO << "INSERT INTO test VALUES (NULL, \"second\")\", returned " << nb;
//
//        // update the second row
//        nb = db.exec("UPDATE test SET value=\"second-updated\" WHERE id='2'");
//        LOG_INFO << "UPDATE test SET value=\"second-updated\" WHERE id='2', returned " << nb;
//
//        // Check the results : expect two row of result
//        SQLite::Statement   query(db, "SELECT * FROM test");
//        LOG_INFO << "SELECT * FROM test :";
//        while (query.executeStep())
//        {
//            LOG_INFO << "row (" << query.getColumn(0) << ", \"" << query.getColumn(1) << "\")";
//        }
//
//        db.exec("DROP TABLE test");
//    }
//    catch (std::exception& e)
//    {
//        LOG_INFO << "SQLite exception: " << e.what();
//        return EXIT_FAILURE; // unexpected error : exit the example program
//    }
//
//    LOG_INFO << "everything ok, quitting";
//
//    return EXIT_SUCCESS;
//}