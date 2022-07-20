#include "Account.hpp"

void Account::create()
{

}

bool Account::get_status() const
{
	return status;
}
void Account::set_status(bool status)
{
	this->status = status;
}

boost::uuids::uuid Account::get_uuid() const
{
	return uuid;
}
void Account::set_uuid(boost::uuids::uuid uuid)
{
	this->uuid = uuid;
}

std::string Account::get_pub_key_fprint() const
{
	return pub_key_fprint;
}
void Account::set_pub_key_fprint(std::string pub_key_fprint)
{
	this->pub_key_fprint = pub_key_fprint;
}

std::string Account::get_username() const
{
	return username;
}
void Account::set_username(std::string username)
{
	this->username = username;
}

std::string Account::get_recovery_phrase() const
{
	return recovery_phrase;
}
void Account::set_recovery_phrase(std::string recovery_phrase)
{
	this->recovery_phrase = recovery_phrase;
}

long Account::get_last_login() const
{
	return last_login;
}
void Account::set_last_login(unsigned long int last_login)
{
	this->last_login = last_login;
}