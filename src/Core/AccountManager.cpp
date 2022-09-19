#include "AccountManager.hpp"

Sentinel::Account Sentinel::AccountManager::create(Username &username, std::string &pub_key_fprint, std::string &recovery_phrase) {
	Account Account;
	Account.set_uuid(uuid_.generage_new());
	Account.set_username(username);
	Account.set_pub_key_fprint(pub_key_fprint);
	Account.set_recovery_phrase(recovery_phrase);

	LOG_INFO << "Creating Account '" << Account.get_uuid() << "'";
	//table_.add_row({Account.get_uuid(), Account.get_username(), Account.get_pub_key_fprint(), Account.get_recovery_phrase().value(), std::to_string(Account.get_status()), std::to_string(Account.get_last_login())});

	return Account;
}

Sentinel::Account Sentinel::AccountManager::update_username(Account &account, Username new_username) {
	// TODO: Validate username

	if (Account.get_username() == new_username)
		return Account;

	if (new_username.is_valid())
		Account.set_username(new_username);

	//table_.update_row_value_where("username", new_username, "uuid", Account.get_uuid());

	return Account;
}

Sentinel::Account Sentinel::AccountManager::update_pkf(Account &account, std::string new_public_key_fingerprint) {
	Account.set_pub_key_fprint(new_public_key_fingerprint);

	//table_.update_row_value_where("public_key_fingerprint", new_public_key_fingerprint, "uuid", Account.get_uuid());

	return Account;
}

Sentinel::Account Sentinel::AccountManager::update_recovery_phrase(Account &account, std::string new_recovery_phrase) {
	Account.set_recovery_phrase(new_recovery_phrase);

	//table_.update_row_value_where("recovery_phrase", new_recovery_phrase, "uuid", Account.get_uuid());

	return Account;
}

Sentinel::Account Sentinel::AccountManager::get_by_uuid(UUID& uuid) {
	std::vector<std::string> vec = table_.get_row_where("uuid", uuid);

	// Ghetto ?
	Account Account;
	Account.set_uuid(UUID(vec.at(0)));
	Account.set_username(vec.at(1));
	Account.set_pub_key_fprint(vec.at(2));
	Account.set_recovery_phrase(vec.at(3));

	return Account;
}

Sentinel::Account Sentinel::AccountManager::get_by_pkf(std::string public_key_fingerprint) {
	std::vector<std::string> vec = table_.get_row_where("public_key_fingerprint", public_key_fingerprint);

	// Ghetto ?
	Account Account;
	Account.set_uuid(UUID(vec.at(0)));
	Account.set_username(vec.at(1));
	Account.set_pub_key_fprint(vec.at(2));
	Account.set_recovery_phrase(vec.at(3));

	return Account;
}

bool Sentinel::AccountManager::login(Account& Account) {
	if (!Account.get_status())
		return false;

	return true;
}

void Sentinel::AccountManager::delete_(Account& Account) {
	Account.set_status(false);

	//table_.delete_row_where_d("uuid", Account.get_uuid(), "public_key_fingerprint", Account.get_pub_key_fprint());
}
