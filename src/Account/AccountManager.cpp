#include "AccountManager.hpp"

Account AccountManager::create(std::string &username, std::string &pub_key_fprint, std::string &recovery_phrase)
{
    account.set_uuid(uuid.generage_new());
    account.set_username(username);
    account.set_pub_key_fprint(pub_key_fprint);
    account.set_recovery_phrase(recovery_phrase);

    LOG_INFO << "Creating account '" << account.get_uuid() << "'";
    table.add_row({account.get_uuid(), account.get_username(), account.get_pub_key_fprint(),
                   account.get_recovery_phrase().value(), account.get_status()
                   /*account.get_status()*/});

    return account;
}

Account AccountManager::update_username(Account &account, std::string new_username)
{
    /*
     * Validate username ?
     */

    if (account.get_username() == new_username)
        return account;

    account.set_username(new_username);

    table.update_value_where("username", new_username, "uuid", account.get_uuid());

    return account;
}

Account AccountManager::update_pkf(Account &account, std::string new_public_key_fingerprint)
{
    account.set_pub_key_fprint(new_public_key_fingerprint);

    table.update_value_where("public_key_fingerprint", new_public_key_fingerprint, "uuid", account.get_uuid());

    return Account();
}

Account AccountManager::update_recovery_phrase(Account &account, std::string new_recovery_phrase)
{
    account.set_recovery_phrase(new_recovery_phrase);

    table.update_value_where("recovery_phrase", new_recovery_phrase, "uuid", account.get_uuid());

    return Account();
}

Account AccountManager::get_by_uuid(Utils::UUID &uuid)
{
    std::vector<std::string> vec = table.get_row_where("uuid", uuid);

    // Ghetto ?
    Account account;
    account.set_uuid(Utils::UUID(vec.at(0)));
    account.set_username(vec.at(1));
    account.set_pub_key_fprint(vec.at(2));
    account.set_recovery_phrase(vec.at(3));

    return account;
}

Account AccountManager::get_by_pkf(std::string public_key_fingerprint)
{
    std::vector<std::string> vec = table.get_row_where("public_key_fingerprint", public_key_fingerprint);

    // Ghetto ?
    Account account;
    account.set_uuid(Utils::UUID(vec.at(0)));
    account.set_username(vec.at(1));
    account.set_pub_key_fprint(vec.at(2));
    account.set_recovery_phrase(vec.at(3));

    return account;
}

bool AccountManager::login(Account &account)
{
    if (account.get_status() == "inactive")
        return false;

    return true;
}

void AccountManager::delete_(Account &account)
{
    account.set_status("inactive");

    table.delete_row_where_d("uuid", account.get_uuid(), "public_key_fingerprint", account.get_pub_key_fprint());
}
