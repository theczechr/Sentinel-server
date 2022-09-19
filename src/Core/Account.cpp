#include "Account.hpp"

Sentinel::UUID Sentinel::Account::get_uuid() const {
	return uuid_;
}

void Sentinel::Account::set_uuid(Sentinel::UUID uuid) {
	require_active_();
	this->uuid_ = uuid;
}

Sentinel::Username Sentinel::Account::get_username() const {
	return username_;
}
void Sentinel::Account::set_username(Username& username) {
	require_active_();

	if (!username.is_valid())
		return;

	this->username_ = username;
}

std::string Sentinel::Account::get_pub_key_fprint() const {
	return pub_key_fprint_;
}
void Sentinel::Account::set_pub_key_fprint(std::string pub_key_fprint) {
	require_active_();

	this->pub_key_fprint_ = pub_key_fprint;
}

std::optional<std::string> Sentinel::Account::get_recovery_phrase() const {
	if (recovery_enabled_)
		return recovery_phrase_;
}
void Sentinel::Account::set_recovery_phrase(std::string recovery_phrase) {
	require_active_();

	this->recovery_enabled_ = true;
	this->recovery_phrase_	= recovery_phrase;
}

Sentinel::Status Sentinel::Account::get_status() const {
	return this->status_;
}
void Sentinel::Account::set_status(Status status) {
	this->status_ = status;
}

Sentinel::UnixTimestamp Sentinel::Account::get_last_login() const {
	return this->last_login_;
}
void Sentinel::Account::set_last_login(UnixTimestamp last_login) {
	this->last_login_ = last_login;
}

void Sentinel::Account::require_active_() {
	assert(status_ == Status::active);

	if (status_ == Status::inactive)
		throw std::runtime_error("Account is inactive");
}
