#pragma once
#include <trantor/utils/Logger.h>
#include "Database.hpp"

/*
* Accounts table (uuid, username, recovery_phrase, status, last_login)
* Messages table (sender uuid, receiver uuid, content, unix time, seen - treba ne)
*/

class Table
{
private:
	std::string table_name;
protected:
	/*
	* First vector is a column name
	* Second vector is a type (https://www.sqlite.org/datatype3.html) and constraint (https://www.tutorialspoint.com/sqlite/sqlite_constraints.htm)
	* * Constraint `UNIQUE` doent work
	*/
	void create(Database db, std::string table_name, std::vector<std::pair<std::string, std::string>> columns);
public:
	Table(Database db, std::string table_name, std::vector<std::pair<std::string, std::string>> columns)
	{
		this->table_name = table_name;
		create(db, this->table_name, columns);
	}

	std::string get_table_name() const;
	// void get_table_content() const; // Jak ziskat Database db ????
};

/*
* Asi neni potreba ?
* Nevim jak chceme udelat disappearing - vim ze se to dela pres TTL (Time To Live) ale jak udelat ? A jestli to jde pres ws
* Prozatim to tady necham
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