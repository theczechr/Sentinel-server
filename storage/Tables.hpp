#pragma once
#include <trantor/utils/Logger.h>
#include "Database.hpp"
#include <boost/algorithm/string/join.hpp> // boost::algorithm::join

/*
 * Accounts table (uuid, username, recovery_phrase, status, last_login)
 * Messages table (sender uuid, receiver uuid, content, unix time, ?)
*/

class Table
{
private:
	Database db;
	std::string table_name;
protected:
	void create(Database& db, std::string table_name, std::vector<std::pair<std::string, std::string>> columns);
public:
	/*
	 * @brief Create new table with columns in database
	 * @note UTF-8 text encoding assumed
	 *
	 * @param[in] db			Initialized class Database
	 * @param[in] table_name	Name of the table you want to create
	 * @param[in] columns		Vector which holds a column name and datatype with constraint - constraint UNIQUE doesn't work
	 * @see Datatypes https://www.sqlite.org/datatype3.html
	 * @see Constraints https://www.tutorialspoint.com/sqlite/sqlite_constraints.htm
	 */
	Table(Database& db, std::string table_name, std::vector<std::pair<std::string, std::string>> columns)
	{
		this->table_name = table_name;
		this->db = db;
		create(this->db, this->table_name, columns);
	}
	/*
	 * @brief Returns table name
	 * @note UTF-8 text encoding assumed
	 *
	 * @return Table name in std::string
	 */
	std::string get_table_name() const;
	/*
	 * @brief Add items into columns
	 * @note UTF-8 text encoding assumed
	 *
	 * @param[in] db			Initialized class Database
	 * @param[in] items			Values you want to insert into an columns
	 */
	void add_items(Database& db, std::vector<std::string> items); // Rename ? - Get rid of `item`
	/*
	 * @brief Check if item exist in table
	 * @note UTF-8 text encoding assumed
	 * 
	 * @param[in] db			Initialized class Database
	 * @param[in] column_name	Name of the column where to look for an item
	 * @param[in] value			Value you searching for
	 * 
	 * @return True if item exist
	*/
	bool item_exist(Database& db, std::string column_name, std::string value); // Rename ? - Get rid of `item`
};

/*
 * Asi neni potreba ?
 * Nevim jak chceme udelat disappearing - vim ze se to dela pres TTL (Time To Live) ale jak to udelat ? A jestli to jde pres ws
 * Prozatim to tady necham
 * Kdybychom to nahodou nejak vyuzili tak bych to prejmenoval tak aby to zacinalo Table
*/

class ExpiringTable : public Table
{
private:
	unsigned long int expiration;
public:
	ExpiringTable(Database db, std::string table_name, unsigned long int expiration, std::vector<std::pair<std::string, std::string>> columns) : Table(db, table_name, columns)
	{
		this->expiration = expiration;
	}

	unsigned long int get_expiration() const;
};