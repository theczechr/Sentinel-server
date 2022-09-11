#include "account_manager.hpp"

sentinel::account sentinel::account_manager::create(std::string &username, std::string &pub_key_fprint, std::string &recovery_phrase) {
	account account;
	account.set_uuid(uuid_.generage_new());
	account.set_username(username);
	account.set_pub_key_fprint(pub_key_fprint);
	account.set_recovery_phrase(recovery_phrase);

	LOG_INFO << "Creating account '" << account.get_uuid() << "'";
	table_.add_row({account.get_uuid(), account.get_username(), account.get_pub_key_fprint(), account.get_recovery_phrase().value(), std::to_string(account.get_status()), std::to_string(account.get_last_login())});

	return account;
}

sentinel::account sentinel::account_manager::update_username(account &account, std::string new_username) {
	// TODO: Validate username

	if (account.get_username() == new_username)
		return account;

	account.set_username(new_username);

	table_.update_row_value_where("username", new_username, "uuid", account.get_uuid());

	return account;
}

sentinel::account sentinel::account_manager::update_pkf(account &account, std::string new_public_key_fingerprint) {
	account.set_pub_key_fprint(new_public_key_fingerprint);

	table_.update_row_value_where("public_key_fingerprint", new_public_key_fingerprint, "uuid", account.get_uuid());

	return account;
}

sentinel::account sentinel::account_manager::update_recovery_phrase(account &account, std::string new_recovery_phrase) {
	account.set_recovery_phrase(new_recovery_phrase);

	table_.update_row_value_where("recovery_phrase", new_recovery_phrase, "uuid", account.get_uuid());

	return account;
}

sentinel::account sentinel::account_manager::get_by_uuid(sentinel::utils::UUID &uuid) {
	std::vector<std::string> vec = table_.get_row_where("uuid", uuid);

	// Ghetto ?
	account account;
	account.set_uuid(sentinel::utils::UUID(vec.at(0)));
	account.set_username(vec.at(1));
	account.set_pub_key_fprint(vec.at(2));
	account.set_recovery_phrase(vec.at(3));

	return account;
}

sentinel::account sentinel::account_manager::get_by_pkf(std::string public_key_fingerprint) {
	std::vector<std::string> vec = table_.get_row_where("public_key_fingerprint", public_key_fingerprint);

	// Ghetto ?
	account account;
	account.set_uuid(sentinel::utils::UUID(vec.at(0)));
	account.set_username(vec.at(1));
	account.set_pub_key_fprint(vec.at(2));
	account.set_recovery_phrase(vec.at(3));

	return account;
}

bool sentinel::account_manager::login(account &account) {
	if (!account.get_status())
		return false;

	return true;
}

void sentinel::account_manager::delete_(account &account) {
	account.set_status(false);

	table_.delete_row_where_d("uuid", account.get_uuid(), "public_key_fingerprint", account.get_pub_key_fprint());
}
