#include "Tables.hpp"

void Table::create(Database& db, std::string table_name, std::vector<std::pair<std::string, std::string>> columns)
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

void Table::add_items(Database& db, std::vector<std::string> items)
{
	LOG_INFO << "Inserting items into table '" << table_name << "'";
	// Implode a vector of strings into a single string
	std::string items_s = boost::algorithm::join(items, "', '");

	db.exec("INSERT INTO " + table_name + " VALUES('" + items_s + "')");
}

bool Table::item_exist(Database& db, std::string column_name, std::string value)
{
	LOG_INFO << "Checking if '" << column_name << "' exist in table '" << table_name << "'";

	if (db.get_db().execAndGet("SELECT EXISTS(SELECT 1 FROM Accounts WHERE " + column_name + " = '" + value + "')").getString() == "0")
	{
		LOG_INFO << "Item '" << column_name << "' doens't exist";
		return false;
	}

	LOG_INFO << "Item '" << column_name << "' exist";
	return true;
}

unsigned long int ExpiringTable::get_expiration() const
{
	return expiration;
}