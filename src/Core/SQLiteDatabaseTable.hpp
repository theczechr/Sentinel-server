#include <trantor/utils/Logger.h>

namespace Sentinel {

	class SQLiteDatabaseTable { // TODO: Change names of std::pair
	  public:
		SQLiteDatabaseTable() {}

		void add_row(std::vector<std::string> row);

		bool value_exist(std::pair<std::string, std::string> column_n_value);
	
		void update_value(std::string column_name, std::pair<std::string, std::string> old_n_new_value);

		void update_row_value_where(std::pair<std::string, std::string> column_n_value, std::pair<std::string, std::string> condition_column_n_value);

		void update_row_value_where_d(std::pair<std::string, std::string> column_n_value, std::pair<std::string, std::string> condition_column_n_value1, std::pair<std::string, std::string> condition_column_n_value2);

		void delete_rows_where(std::pair<std::string, std::string> condition_column_n_value);

		void delete_row_where_d(std::pair<std::string, std::string> condition_column_n_value1, std::pair<std::string, std::string> condition_column_n_value2);

		std::vector<std::string> get_row_where(std::pair<std::string, std::string> condition_column_n_value);

		std::vector<std::string> get_row_where_d(std::pair<std::string, std::string> condition_column_n_value1, std::pair<std::string, std::string> condition_column_n_value2);
	};
}