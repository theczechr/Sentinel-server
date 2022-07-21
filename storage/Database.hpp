#pragma once
#include <trantor/utils/Logger.h>
#include <SQLiteCpp/SQLiteCpp.h>
#include "utils.hpp"

/*
 * Server db: uuid, public key fingerprint, username, recovery phrase, last login
1. Registrace
    - Username
    - Zeptat se pokud bude chtit moznost obnoveni
    1. Ano chce
        - Zada recovery phrase
        - Vytvoreni private, public key (lokalne)
        - Poslani public key fingerprintu a hashed passphrase na server
    2. Nechce
        - Vytvoreni private, public key (lokalne)
        - Poslani public key fingerprintu na server
2. Login
    1. QR code z druheho zarizeni
        - Nejak se prevedou vsechny chaty atd.
    2. Recovery
        - Zada recovery phrase
        - Pokud je spravne (jak se zjisti jestli je spravne ??) 
            - Vytvoreni noveho private, public key (lokalne)
            - Poslani noveho public key fingerprintu na server
            - Prihlaseni pod stejnym acc
        - Pokud neni
            - Znova registrace
*/

/*
 * Client vzdycky posle uuid
 * Sqlitecpp ma execAndGet
 * Taky mne vadi nebo jak bych to rekl ze v .cpp vytvarime v kazde funkci znova SQLite::Database db.. zkousel jsem to dat sem, ale to nejde (nebo nevim jak)
 * Tpc doufam ze si jednou ty notes prectes : DDD (20.6.2022 19:00)
*/

class Database
{
private:
    std::string db_name = "krapp.db";
public:
    Database()
    {
        create();
    }

    std::string get_db_name() const;
    SQLite::Database get_db() const;

    void create();
    void create_table(std::string table_name);
    void exec(std::string command);
    void drop_table(std::string table_name);
};