#include "AccountManager.hpp"

sentinel::account sentinel::account_manager::create(std::string &username, std::string &pub_key_fprint, std::string &recovery_phrase) {
	account account;
	account.set_uuid(uuid_.generage_new());
	account.set_username(username);
	account.set_pub_key_fprint(pub_key_fprint);
	account.set_recovery_phrase(recovery_phrase);

	LOG_INFO << "Creating account '" << account.get_uuid() << "'";
	// table_.add_row({account.get_uuid(), account.get_username(), account.get_pub_key_fprint(), account.get_recovery_phrase().value(), std::to_string(account.get_status()), std::to_string(account.get_last_login())});

	// Index in memory for PoC
	pkf_to_account_[pub_key_fprint] = account;

	return account;
}

sentinel::account sentinel::account_manager::update_username(account &account, std::string new_username) {
	// TODO: Validate username

	if (account.get_username() == new_username)
		return account;

	account.set_username(new_username);

	// table_.update_row_value_where("username", new_username, "uuid", account.get_uuid());

	// refresh in-memory index if present
	pkf_to_account_[account.get_pub_key_fprint()] = account;

	return account;
}

sentinel::account sentinel::account_manager::update_pkf(account &account, std::string new_public_key_fingerprint) {
	// erase old index
	pkf_to_account_.erase(account.get_pub_key_fprint());
	erase_public_key_for_pkf(account.get_pub_key_fprint());

	account.set_pub_key_fprint(new_public_key_fingerprint);

	// table_.update_row_value_where("public_key_fingerprint", new_public_key_fingerprint, "uuid", account.get_uuid());

	// reindex
	pkf_to_account_[new_public_key_fingerprint] = account;

	return account;
}

sentinel::account sentinel::account_manager::update_recovery_phrase(account &account, std::string new_recovery_phrase) {
	account.set_recovery_phrase(new_recovery_phrase);

	// table_.update_row_value_where("recovery_phrase", new_recovery_phrase, "uuid", account.get_uuid());

	return account;
}

sentinel::account sentinel::account_manager::get_by_uuid(sentinel::utils::UUID &uuid) {
	// std::vector<std::string> vec = table_.get_row_where("uuid", uuid);

	// Ghetto ?
	account account;
	// account.set_uuid(sentinel::utils::UUID(vec.at(0)));
	// account.set_username(vec.at(1));
	// account.set_pub_key_fprint(vec.at(2));
	// account.set_recovery_phrase(vec.at(3));

	return account;
}

sentinel::account sentinel::account_manager::get_by_pkf(std::string public_key_fingerprint) {
	// Prefer in-memory map
	auto it = pkf_to_account_.find(public_key_fingerprint);
	if (it != pkf_to_account_.end()) {
		return it->second;
	}

	// std::vector<std::string> vec = table_.get_row_where("public_key_fingerprint", public_key_fingerprint);

	// Ghetto ?
	account account;
	// account.set_uuid(sentinel::utils::UUID(vec.at(0)));
	// account.set_username(vec.at(1));
	// account.set_pub_key_fprint(vec.at(2));
	// account.set_recovery_phrase(vec.at(3));

	return account;
}

bool sentinel::account_manager::login(account &account) {
	if (!account.get_status())
		return false;

	return true;
}

void sentinel::account_manager::delete_(account &account) {
	account.set_status(false);

	pkf_to_account_.erase(account.get_pub_key_fprint());
	erase_public_key_for_pkf(account.get_pub_key_fprint());
	// table_.delete_row_where_d("uuid", account.get_uuid(), "public_key_fingerprint", account.get_pub_key_fprint());
}

std::optional<std::string> sentinel::account_manager::get_public_key_by_pkf(const std::string &public_key_fingerprint) const {
	return key_store_.get_by_fingerprint(public_key_fingerprint);
}

void sentinel::account_manager::upsert_public_key_for_pkf(const std::string &public_key_fingerprint, const std::string &public_key) {
	key_store_.upsert(public_key_fingerprint, public_key);
}

void sentinel::account_manager::erase_public_key_for_pkf(const std::string &public_key_fingerprint) {
	key_store_.erase(public_key_fingerprint);
}
