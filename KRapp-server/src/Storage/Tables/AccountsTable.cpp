#include "AccountsTable.hpp"

void AccountsTable::create_account(std::string& pub_key_fprint, std::string& username, std::string& recovery_phrase, Core::UNIX_TS& last_login)
{
	Core::UUID UUID;

	LOG_INFO << "Creating new account '" << UUID.to_string() << "'";
	add_row({ UUID.to_string(), pub_key_fprint, username, recovery_phrase, "1", last_login.to_string()});
	LOG_INFO << "Account created successfully";
}

void AccountsTable::delete_account(Core::UUID& uuid, std::string& pub_key_fprint)
{
	LOG_INFO << "Deleting account '" << uuid.to_string();
	delete_row_where_d("uuid", uuid.to_string(), "pub_key_fprint", pub_key_fprint);
	LOG_INFO << "Account deleted successfully";
}

void AccountsTable::change_username(Core::UUID& uuid, std::string& pub_key_fprint, std::string& username)
{
	LOG_INFO << "Changing username on account '" << uuid.to_string();
	update_value_where("username", username, "uuid", uuid.to_string());
	LOG_INFO << "Username changed successfully";
}

void AccountsTable::change_pub_key_fprint(std::string& old_pub_key_fprint, std::string& new_pub_key_fprint)
{
	LOG_INFO << "Changing public key fingerprint";
	update_value("pub_key_fprint", old_pub_key_fprint, new_pub_key_fprint);
	LOG_INFO << "Public key fingerprint changed successfully";
}

void AccountsTable::change_recovery_phrase(Core::UUID uuid, std::string& pub_key_fprint, std::string& recovery_phrase)
{
	LOG_INFO << "Changing recovery phrase on account '" << uuid.to_string();
	update_value_where("recovery_phrase", recovery_phrase, "uuid", uuid.to_string());
	LOG_INFO << "Recovery phrase changed successfully";
}

bool AccountsTable::login_account(std::string& pub_key_fprint, Core::UNIX_TS& last_login)
{
	if (!value_exist("pub_key_fprint", pub_key_fprint))
		return false; // Returnout nejakej error code ? Jak ?

	update_value_where("last_login", last_login.to_string(), "pub_key_fprint", pub_key_fprint);
	return true;
}