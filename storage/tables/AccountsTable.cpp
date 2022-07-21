#include "AccountsTable.hpp"

/*
* Jak vyuzit vsude ten pub_key_fprint ?
*/

void AccountsTable::create_account(std::string& pub_key_fprint, std::string& username, std::string& recovery_phrase, unsigned long int& last_login)
{
	Account account(pub_key_fprint, username, recovery_phrase, last_login); // <- unresolved external symbol

	LOG_INFO << "Creating new account '" << boost::uuids::to_string(account.get_uuid()) << "'";
	add_row({ boost::uuids::to_string(account.get_uuid()), account.get_pub_key_fprint(), account.get_username(), account.get_recovery_phrase(), std::to_string(account.get_last_login()) });
	LOG_INFO << "Account created successfully";
}

void AccountsTable::delete_account(boost::uuids::uuid& uuid, std::string& pub_key_fprint)
{
	LOG_INFO << "Deleting account '" << boost::uuids::to_string(uuid);
	delete_row_where_d("uuid", boost::uuids::to_string(uuid), "pub_key_fprint", pub_key_fprint);
	LOG_INFO << "Account deleted successfully";
}

void AccountsTable::change_username(boost::uuids::uuid& uuid, std::string& pub_key_fprint, std::string& username)
{
	LOG_INFO << "Changing username on account '" << boost::uuids::to_string(uuid);
	update_value_where("username", username, "uuid", boost::uuids::to_string(uuid));
	LOG_INFO << "Username changed successfully";
}

void AccountsTable::change_pub_key_fprint(std::string& pub_key_fprint, std::string& recovery_phrase)
{
	LOG_INFO << "Changing public key fingerprint";
	// Jak se zjisti jestli je spravne ??
	LOG_INFO << "Public key fingerprint changed successfully";
}

void AccountsTable::change_recovery_phrase(boost::uuids::uuid uuid, std::string& pub_key_fprint, std::string& recovery_phrase)
{
	LOG_INFO << "Changing recovery phrase on account '" << boost::uuids::to_string(uuid);
	update_value_where("recovery_phrase", recovery_phrase, "uuid", boost::uuids::to_string(uuid));
	LOG_INFO << "Recovery phrase changed successfully";
}

bool AccountsTable::login_account(std::string& pub_key_fprint, unsigned long int& last_login)
{
	return false;
}