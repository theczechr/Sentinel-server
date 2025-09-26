#include "Account.hpp"

sentinel::utils::UUID sentinel::account::get_uuid() const {
	return uuid_;
}

void sentinel::account::set_uuid(sentinel::utils::UUID uuid) {
	require_active();
	this->uuid_ = uuid;
}

std::string sentinel::account::get_username() const {
	return username_;
}
void sentinel::account::set_username(std::string username) {
	require_active();

	this->username_ = username;
}

std::string sentinel::account::get_pub_key_fprint() const {
	return pub_key_fprint_;
}
void sentinel::account::set_pub_key_fprint(std::string pub_key_fprint) {
	require_active();

	this->pub_key_fprint_ = pub_key_fprint;
}

std::optional<std::string> sentinel::account::get_public_key() const {
	return public_key_;
}
void sentinel::account::set_public_key(const std::string &public_key) {
	require_active();
	this->public_key_ = public_key;
}

std::optional<std::string> sentinel::account::get_recovery_phrase() const {
	if (recovery_enabled_)
		return recovery_phrase_;
}
void sentinel::account::set_recovery_phrase(std::string recovery_phrase) {
	require_active();

	this->recovery_enabled_ = true;
	this->recovery_phrase_	= recovery_phrase;
}

bool sentinel::account::get_status() const {
	return this->status_;
}
void sentinel::account::set_status(bool status) {
	this->status_ = status;
}

unsigned long long sentinel::account::get_last_login() const {
	return this->last_login_;
}

void sentinel::account::set_last_login(unsigned long long last_login) {
	this->last_login_ = last_login;
}

void sentinel::account::require_active() {
	if (!this->status_)
		throw("Account '" + (std::string) this->uuid_ + "' is not active");
}
