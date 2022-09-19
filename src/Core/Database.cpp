#include "Database.hpp"

void Sentinel::Database::create_(std::string& name) {
	LOG_INFO << "SQlite3 version " << SQLite::VERSION << " (" << SQLite::getLibVersion() << ")";
	LOG_INFO << "SQliteC++ version " << SQLITECPP_VERSION;
	LOG_INFO << "Creating new database file '" << name << "'";

	if (file_exist_(name)) {
		LOG_ERROR << "SQLite database file '" << name << "' already exist, quitting";
		return;
	}

	this->name_ = name;
	SQLite::Database db(name, SQLite::OPEN_CREATE | SQLite::OPEN_READWRITE);
	LOG_INFO << "SQLite database file '" << name << "' created successfully. quitting";
}

bool Sentinel::Database::file_exist_(std::string file) {
	std::ifstream ifile;
	ifile.open(file);
	if (!ifile)
		return false;
	return true;
}

void Sentinel::Database::create_table(std::string table_name) {
	LOG_INFO << "Creating table '" << table_name << "'";

	if (!file_exist_(this->name_)) {
		LOG_ERROR << "SQLite database file '" << this->name_ << "' doesn't exist, quitting";
		return;
	}

	if (this->db_connector.tableExists(table_name)) {
		LOG_ERROR << "Table '" + table_name + "' already exist, quitting";
		return;
	}

	// Zero-column tables aren't supported in SQLite. In the SQL standard either.
	this->db_connector.exec("CREATE TABLE " + table_name + " (columnn INTEGER NOT NULL)");

	LOG_INFO << "Table '" + table_name + "' created successfully, quitting";
}

void Sentinel::Database::exec(std::string command) {
	LOG_INFO << "Executing '" << command << "' into '" << this->name_ << "'";

	if (!file_exist_(this->name_)) {
		LOG_ERROR << "SQLite database file '" << this->name_ << "' doesn't exist, quitting";
		return;
	}

	try {
		this->db_connector.exec(command);
	} catch (std::exception& e) {
		LOG_ERROR << "SQLite exception '" << e.what() << "'";
		return;
	}

	LOG_INFO << "Command executed, quitting";
}

void Sentinel::Database::drop_table(std::string table_name) {
	LOG_INFO << "Dropping table '" << table_name << "'";

	if (!file_exist_(this->name_)) {
		LOG_ERROR << "SQLite database file '" << this->name_ << "' doesn't exist, quitting";
		return;
	}

	if (!this->db_connector.tableExists(table_name)) {
		LOG_ERROR << "Table '" + table_name + "' doesn't exist";
		return;
	}

	this->db_connector.exec("DROP TABLE " + table_name);

	LOG_INFO << "Table '" + table_name + "' was dropped successfully, quitting";
}
