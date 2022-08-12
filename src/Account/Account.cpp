#include "Account.hpp"

Utils::UUID Account::get_uuid() const
{
    return uuid;
}

void Account::set_uuid(Utils::UUID uuid)
{
    require_active();
    this->uuid = uuid;
}

std::string Account::get_username() const
{
    return username;
}
void Account::set_username(std::string username)
{
    require_active();

    this->username = username;
}

std::string Account::get_pub_key_fprint() const
{
    return pub_key_fprint;
}
void Account::set_pub_key_fprint(std::string pub_key_fprint)
{
    require_active();

    this->pub_key_fprint = pub_key_fprint;
}

std::optional<std::string> Account::get_recovery_phrase() const
{
    if (recovery_enabled)
        return recovery_phrase;
}
void Account::set_recovery_phrase(std::string recovery_phrase)
{
    require_active();

    this->recovery_enabled = true;
    this->recovery_phrase = recovery_phrase;
}

std::string Account::get_status() const
{
    return this->status ? "active" : "false";
}
void Account::set_status(std::string status)
{
    if (status == "inactive")
        this->status = false;
    else
        this->status = true;
}

void Account::require_active()
{
    if (status)
    {
        throw("Account '" + (std::string)this->uuid + "' is not active");
    }
}
