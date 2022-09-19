#pragma once
#include "DatabaseTables.hpp"

namespace Sentinel {
	namespace Configuration {

		class AccountsTableConfiguration : public DatabaseTables::Table {
		  public:
			AccountsTableConfiguration() {}
			//AccountsTableConfiguration(std::string table_name) {
			//	DatabaseTables::Table::set_table_name(table_name);
			//}
		};

	}// namespace Configuration
}// namespace Sentinel
