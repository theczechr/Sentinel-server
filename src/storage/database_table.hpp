#pragma once
#include "Database.hpp"

#include <boost/algorithm/string/join.hpp>// boost::algorithm::join
#include <trantor/utils/Logger.h>

/*
 * Accounts table (uuid, username, recovery_phrase, status, last_login)
 * Messages table (sender uuid, receiver uuid, content, unix time, ?)
 */

namespace sentinel {
	namespace storage {

		class table {
		  public:
			table() {}

			/*
             * @brief Create new table with columns in database
             *
             * @param[in] table_name	Name of the table you want to create
             * @param[in] columns		Vector which holds a column name and datatype with constraint - constraint UNIQUE doesn't work
             * @see Datatypes https://www.sqlite.org/datatype3.html
             * @see Constraints
             * https://www.tutorialspoint.com/sqlite/sqlite_constraints.htm
             */
			table(std::string table_name, std::vector<std::pair<std::string, std::string>> columns) {
				this->_name = table_name;
				_create(columns);
			}

			void add_row(std::vector<std::string> row);

			/*
             * @brief Check if value exists in column
             *
             * @return True if exist
             */
			bool value_exist(std::string column_name, std::string value);

			/*
             * @brief Update value in a column with existing value
             */
			void update_value(std::string column_name, std::string old_value, std::string new_value);

			/*
             * @brief Update value in a specific row - one condition
             */
			void update_row_value_where(std::string value_column, std::string value, std::string condition_column, std::string condition_value);

			/*
             * @brief Update value in a specific row - two conditions
             */
			void update_row_value_where_d(std::string value_column, std::string value, std::string condition_column1, std::string condition_value1, std::string condition_column2, std::string condition_value2);

			/*
             * @brief Delete row - one condition
             */
			void delete_rows_where(std::string condition_column, std::string condition_value);

			/*
             * @brief Delete row - two conditions
             */
			void delete_row_where_d(std::string condition_column1, std::string condition_value1, std::string condition_column2, std::string condition_value2);

			/*
             * @brief Get row - one condition
             *
             * @return Filled vector with row
             */
			std::vector<std::string> get_row_where(std::string condition_column, std::string condition_value);

			/*
             * @brief Get row - two conditions
             *
             * @return Filled vector with row
             */
			std::vector<std::string> get_row_where_d(std::string condition_column1, std::string condition_value1, std::string condition_column2, std::string condition_value2);

		  private:
			database	_db;
			std::string _name;
			void		_create(std::vector<std::pair<std::string, std::string>> &columns);
		};

	}// namespace storage
}// namespace sentinel
