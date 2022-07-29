#include "Database.hpp"

std::string storage::Database::get_name() const
{
	return db_name;
}

SQLite::Database storage::Database::get_db() const
{
	SQLite::Database db(db_name, SQLite::OPEN_READWRITE);
	return db;
}

void storage::Database::create()
{
    LOG_INFO << "SQlite3 version " << SQLite::VERSION << " (" << SQLite::getLibVersion() << ")";
    LOG_INFO << "SQliteC++ version " << SQLITECPP_VERSION;
    LOG_INFO << "Creating new database file '" << db_name << "'";

	if (Utils::file_exist(db_name))
	{
		LOG_ERROR << "SQLite database file '" << db_name << "' already exist, quitting";
		return;
	}

	SQLite::Database db(db_name, SQLite::OPEN_CREATE | SQLite::OPEN_READWRITE);
	LOG_INFO << "SQLite database file '" << db_name << "' created successfully. quitting";
}

void storage::Database::create_table(std::string table_name)
{
	LOG_INFO << "SQlite3 version " << SQLite::VERSION << " (" << SQLite::getLibVersion() << ")";
	LOG_INFO << "SQliteC++ version " << SQLITECPP_VERSION;
	LOG_INFO << "Creating table '" << table_name << "'";

	if (!Utils::file_exist(db_name))
	{
		LOG_ERROR << "SQLite database file '" << db_name << "' doesn't exist, quitting";
		return;
	}

	SQLite::Database db(db_name, SQLite::OPEN_READWRITE);

	if (db.tableExists(table_name))
	{
		LOG_ERROR << "Table '" + table_name + "' already exist, quitting";
		return;
	}
	
	// Zero-column tables aren't supported in SQLite. Or in the SQL standard either.
	db.exec("CREATE TABLE " + table_name + " (columnn INTEGER NOT NULL)");

	LOG_INFO << "Table '" + table_name + "' created successfully, quitting";
}

void storage::Database::exec(std::string command)
{
	LOG_INFO << "SQlite3 version " << SQLite::VERSION << " (" << SQLite::getLibVersion() << ")";
	LOG_INFO << "SQliteC++ version " << SQLITECPP_VERSION;
	LOG_INFO << "Executing command into '" << db_name << "'";

	if (!Utils::file_exist(db_name))
	{
		LOG_ERROR << "SQLite database file '" << db_name << "' doesn't exist, quitting";
		return;
	}

	// Needed, because we don't know what will be executed here so we can't catch the error
	try
	{
		SQLite::Database db(db_name, SQLite::OPEN_READWRITE);
		db.exec(command);
	}
	catch (std::exception& e)
	{
		LOG_ERROR << "SQLite exception '" << e.what() << "'";
		return;
	}

	LOG_INFO << "Command executed, quitting";
}

void storage::Database::drop_table(std::string table_name)
{
	LOG_INFO << "SQlite3 version " << SQLite::VERSION << " (" << SQLite::getLibVersion() << ")";
	LOG_INFO << "SQliteC++ version " << SQLITECPP_VERSION;
	LOG_INFO << "Dropping table '" << table_name << "'";

	if (!Utils::file_exist(db_name))
	{
		LOG_ERROR << "SQLite database file '" << db_name << "' doesn't exist, quitting";
		return;
	}

	SQLite::Database db(db_name, SQLite::OPEN_CREATE | SQLite::OPEN_READWRITE);

	if (!db.tableExists(table_name))
	{
		LOG_ERROR << "Table '" + table_name + "' doesn't exist";
		return;
	}

	db.exec("DROP TABLE " + table_name);

	LOG_INFO << "Table '" + table_name + "' was dropped successfully, quitting";
}