#include "Tables.hpp"

void Table::create(Database db, std::string table_name, std::vector<std::pair<std::string, std::string>> columns)
{
	db.create_table(table_name);
	for (auto &column : columns)
	{
		LOG_INFO << column.first << ", " << column.second;
		db.exec("ALTER TABLE " + table_name + " ADD COLUMN " + column.first + " " + column.second + "");
	}

	// Deleting temp. column
	db.exec("ALTER TABLE " + table_name + " DROP COLUMN columnn");
}

std::string Table::get_table_name() const
{
	return table_name;
}

unsigned long int ExpiringTable::get_expiration() const
{
	return expiration;
}