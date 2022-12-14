/*
#pragma once
#include "Database.hpp"

#include <boost/algorithm/string/join.hpp>// boost::algorithm::join
#include <trantor/utils/Logger.h>

namespace sentinel {
	namespace storage {

		class table {
		  public:
			table() {}

			table(std::string table_name, std::vector<std::pair<std::string, std::string>> columns) {
				this->_name = table_name;
				_create(columns);
			}

			void add_row(std::vector<std::string> row);

			bool value_exist(std::string column_name, std::string value);

			void update_value(std::string column_name, std::string old_value, std::string new_value);

			void update_row_value_where(std::string value_column, std::string value, std::string condition_column, std::string condition_value);

			void update_row_value_where_d(std::string value_column, std::string value, std::string condition_column1, std::string condition_value1, std::string condition_column2, std::string condition_value2);

			void delete_rows_where(std::string condition_column, std::string condition_value);

			void delete_row_where_d(std::string condition_column1, std::string condition_value1, std::string condition_column2, std::string condition_value2);

			std::vector<std::string> get_row_where(std::string condition_column, std::string condition_value);

			std::vector<std::string> get_row_where_d(std::string condition_column1, std::string condition_value1, std::string condition_column2, std::string condition_value2);

		  private:
			database	_db;
			std::string _name;
			void		_create(std::vector<std::pair<std::string, std::string>> &columns);
		};

	}// namespace storage
}// namespace sentinel

*/