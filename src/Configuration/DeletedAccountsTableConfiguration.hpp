#pragma once
#include "DatabaseTables.hpp"

namespace Sentinel {
	namespace Configuration {

		class DeletedAccountsTableConfiguration : public DatabaseTables::Table {
		  public:
			DeletedAccountsTableConfiguration() {}
		};

	}// namespace Configuration
}// namespace Sentinel
