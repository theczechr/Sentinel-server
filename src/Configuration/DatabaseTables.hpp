#pragma once
#include "AccountsTableConfiguration.hpp"
#include "DeletedAccountsTableConfiguration.hpp"

#include <boost/algorithm/string/join.hpp>// boost::algorithm::join
#include <trantor/utils/Logger.h>

namespace Sentinel {
	namespace Configuration {

		class DatabaseTables {
		  public:
			class Table {
			  public:
				Table() {}
				Table(std::string table_name) : name_(table_name) {}

				std::string get_table_name() const { return name_; }
				void		set_table_name(std::string& table_name) { this->name_ = table_name; }

			  protected:
				std::string name_;
				//std::vector<std::pair<std::string, std::string>> columns_;
			};

			class TableWithExpiration : public Table {
			  public:
				TableWithExpiration() {}
				TableWithExpiration(std::string table_name, unsigned long expiration) : Table() {
					Table::set_table_name(table_name);
					this->expiration_ = expiration;
				}

				unsigned long get_expiration() { return expiration_; }
				void		  set_expiration(unsigned long& expiration) { this->expiration_ = expiration; }

			  private:
				unsigned long expiration_;
			};

			DatabaseTables() {}
			DatabaseTables(AccountsTableConfiguration accounts, DeletedAccountsTableConfiguration deleted_accounts) {
				this->accounts_			= accounts;
				this->deleted_accounts_ = deleted_accounts;
			}

			AccountsTableConfiguration		  get_accounts() { return accounts_; }
			DeletedAccountsTableConfiguration get_deleted_accounts() { return deleted_accounts_; }

		  private:
			AccountsTableConfiguration		  accounts_;
			DeletedAccountsTableConfiguration deleted_accounts_;
		};

	}// namespace Configuration
}// namespace Sentinel

 /*
	namespace Configuration {

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

			void update_row_value_where(std::vector<std::pair<std::string, std::string>> value, std::vector<std::pair<std::string, std::string>> condition);

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

	}// namespace Configuration

	*/
