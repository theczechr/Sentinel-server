#include "account.hpp"

int Account::get_version()
{
	return verion;
}
void Account::set_version(int version)
{
	Account::verion = version;
}

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

std::string Account::get_username()
{
	return username;
}
void Account::set_username(std::string username)
{
	Account::username = username;
}

std::string Account::get_email_hash()
{
	return email_hash;
}
void Account::set_email_hash(std::string email_hash)
{
	Account::email_hash = email_hash;
}

std::string Account::get_password_hash()
{
	return password_hash;
}
void Account::set_password_hash(std::string password_hash)
{
	Account::password_hash = password_hash;
}

std::string Account::get_number_hash()
{
	return number_hash;
}
void Account::set_number_hash(std::string number_hash)
{
	Account::number_hash = number_hash;
}