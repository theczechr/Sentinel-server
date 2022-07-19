#pragma once
#include <trantor/utils/Logger.h>
#include <SQLiteCpp/SQLiteCpp.h>
#include "utils.hpp"

/*
* Server db: uuid, public key, username, recovery phrase, last login
1. Registrace
    - Username
    - Zeptat se pokud bude chtit moznost obnoveni
    1. Ano chce
        - Zada recovery phrase
        - Vytvoreni private, public key (lokalne)
        - Poslani public key a hashed passphrase na server
    2. Nechce
        - Vytvoreni private, public key (lokalne)
        - Poslani public key na server
2. Login
    1. QR code z druheho zarizeni
        - Stazeni public key a vsech chatu atd.
    2. Recovery
        - Zada recovery phrase
        - Pokud je spravne
            - Vytvoreni noveho private, public key (lokalne)
            - Poslani noveho public key na server
            - Prihlaseni pod stejnym acc
        - Pokud neni
            - Znova registrace
*/

/*
* Client vzdycky posle uuid
* Sqlitecpp ma execAndGet
*/

class Database
{
private:
    const std::string db_name = "krapp.db";
public:
    Database()
    {
        create();
    }

    std::string get_db_name() const;

    void create();
    void create_table(std::string table_name);
    void exec(std::string command);
    void drop_table(std::string table_name);
};