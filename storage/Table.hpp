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
	void create(std::vector<std::pair<std::string, std::string>> columns);
public:
	/*
	 * @brief Create new table with columns in database
	 * @note UTF-8 text encoding assumed
	 *
	 * @param[in] db			Instantiate Database
	 * @param[in] table_name	Name of the table you want to create
	 * @param[in] columns		Vector which holds a column name and datatype with constraint - constraint UNIQUE doesn't work
	 * @see Datatypes https://www.sqlite.org/datatype3.html
	 * @see Constraints https://www.tutorialspoint.com/sqlite/sqlite_constraints.htm
	 */
	Table(Database& db, std::string table_name, std::vector<std::pair<std::string, std::string>> columns)
	{
		this->db = db;
		this->table_name = table_name;
		create(columns);
	}

	/*
	 * @brief Returns table name
	 *
	 * @return Table name in std::string
	 */
	std::string get_table_name() const;

	/*
	 * @brief Add row to table
	 */
	void add_row(std::vector<std::string> row);

	/*
	 * @brief Check if column exists in database
	 *
	 * @return True if column exist
	*/
	bool column_exist(std::string column_name);

	/*
	 * @brief Check if value exists in column
	 * 
	 * @return True if value exist
	*/
	bool value_exist(std::string column_name, std::string value);

	/*
	 * @brief Update value in a column with existing value
	*/
	void update_value(std::string column_name, std::string old_value, std::string new_value);

	/*
	 * @brief Update a specific row value
	*/
	void update_value_where(std::string value_column, std::string value, std::string condition_column, std::string condition_value);

	/*
	 * @brief Update a specific row value
	*/
	void update_value_where_d(std::string value_column, std::string value, std::string condition_column1, std::string condition_value1, std::string condition_column2, std::string condition_value2);

	/*
	 * @brief Delete rows that matches condition
	*/
	void delete_rows_where(std::string condition_column, std::string condition_value);

	/*
	 * @brief Delete row that matches two conditions (for deleting account)
	*/
	void delete_row_where_d(std::string condition_column1, std::string condition_value1, std::string condition_column2, std::string condition_value2);
};

/*
 * Asi neni potreba ?
 * Nevim jak chceme udelat disappearing - vim ze se to dela pres TTL (Time To Live) ale jak to udelat ? A jestli to jde pres ws
 * Prozatim to tady necham
 * Kdybychom to nahodou nejak vyuzili tak bych to prejmenoval tak aby to zacinalo Table
*/