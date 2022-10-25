#include "database.hpp"

void sentinel::storage::database::_create(std::string &name) {
	LOG_INFO << "SQlite3 version " << SQLite::VERSION << " (" << SQLite::getLibVersion() << ")";
	LOG_INFO << "SQliteC++ version " << SQLITECPP_VERSION;
	LOG_INFO << "Creating new database file '" << name << "'";

	if (_file_exist(name)) {
		LOG_ERROR << "SQLite database file '" << name << "' already exist, quitting";
		return;
	}

	_name = name;
	SQLite::Database db(name, SQLite::OPEN_CREATE | SQLite::OPEN_READWRITE);
	LOG_INFO << "SQLite database file '" << name << "' created successfully. quitting";
}

bool sentinel::storage::database::_file_exist(std::string file) {
	std::ifstream ifile;
	ifile.open(file);
	if (!ifile)
		return false;
	return true;
}

void sentinel::storage::database::create_table(std::string table_name) {
	LOG_INFO << "Creating table '" << table_name << "'";

	if (!_file_exist(this->_name)) {
		LOG_ERROR << "SQLite database file '" << this->_name << "' doesn't exist, quitting";
		return;
	}

	if (this->db.tableExists(table_name)) {
		LOG_ERROR << "Table '" + table_name + "' already exist, quitting";
		return;
	}

	// Zero-column tables aren't supported in SQLite. In the SQL standard either.
	this->db.exec("CREATE TABLE " + table_name + " (columnn INTEGER NOT NULL)");

	LOG_INFO << "Table '" + table_name + "' created successfully, quitting";
}

void sentinel::storage::database::exec(std::string command) {
	LOG_INFO << "Executing '" << command << "' into '" << this->_name << "'";

	if (!_file_exist(this->_name)) {
		LOG_ERROR << "SQLite database file '" << this->_name << "' doesn't exist, quitting";
		return;
	}

	try {
		this->db.exec(command);
	} catch (std::exception &e) {
		LOG_ERROR << "SQLite exception '" << e.what() << "'";
		return;
	}

	LOG_INFO << "Command executed, quitting";
}

void sentinel::storage::database::drop_table(std::string table_name) {
	LOG_INFO << "Dropping table '" << table_name << "'";

	if (!_file_exist(this->_name)) {
		LOG_ERROR << "SQLite database file '" << this->_name << "' doesn't exist, quitting";
		return;
	}

	if (!this->db.tableExists(table_name)) {
		LOG_ERROR << "Table '" + table_name + "' doesn't exist";
		return;
	}

	this->db.exec("DROP TABLE " + table_name);

	LOG_INFO << "Table '" + table_name + "' was dropped successfully, quitting";
}
