#pragma once
#include "Account.hpp"
#include "Table.hpp"

class AccountManager {
public:
  AccountManager() {
    this->table =
        storage::Table("Accounts", {
                                       {"uuid", "TEXT NOT NULL"},
                                       {"username", "TEXT NOT NULL"},
                                       {"pub_key_fprint", "TEXT NOT NULL"},
                                       {"recovery_phrase", "TEXT"},
                                       {"status", "TEXT NOT NULL"}
                                       //{"last_login", "INTEGER NOT NULL"}
                                   });
  }

  Account create(std::string &username, std::string &pub_key_fprint,
                 std::string &recovery_phrase);
  Account update_username(Account &account, std::string new_username);
  Account update_pkf(Account &account, std::string new_public_key_fingerprint);
  Account update_recovery_phrase(Account &account,
                                 std::string new_recovery_phrase);
  Account get_by_uuid(Utils::UUID &uuid);
  Account get_by_pkf(std::string public_key_fingerprint);

  bool login(Account &account);
  void delete_(Account &account);

private:
  Account account;
  Utils::UUID uuid;
  storage::Table table;
  int column_num = 6;
};
