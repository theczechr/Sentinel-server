#include "account.hpp"

bool Account::get_status()
{
	return status;
}
void Account::set_status(bool status)
{
	Account::status = status;
}

std::string Account::get_uuid()
{
	return uuid;
}
void Account::set_uuid(std::string uuid)
{
	Account::uuid = uuid;
}

Botan::RSA_PublicKey Account::get_pub_key()
{
	return Account::pub_key;
}
void Account::set_pub_key(Botan::RSA_PublicKey pub_key)
{
	Account::pub_key = pub_key;
}

std::string Account::get_username()
{
	return username;
}
void Account::set_username(std::string username)
{
	Account::username = username;
}

std::string Account::get_recovery_phrase()
{
	return recovery_phrase;
}
void Account::set_recovery_phrase(std::string recovery_phrase)
{
	Account::recovery_phrase = recovery_phrase;
}

long Account::get_last_login()
{
	return last_login;
}
void Account::set_last_login(long last_login)
{
	Account::last_login = last_login;
}