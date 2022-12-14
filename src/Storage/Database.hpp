/*
#pragma once
#include <SQLiteCpp/SQLiteCpp.h>
#include <fstream>
#include <trantor/utils/Logger.h>


Server db: uuid, public key fingerprint, username, recovery phrase, last
login
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


namespace sentinel {
	namespace storage {

		class database {
		  public:
			database() {}
			database(std::string name) {
				_create(name);
			}

			void create_table(std::string table_name);
			void exec(std::string command);
			void drop_table(std::string table_name);

			SQLite::Database db = SQLite::Database(this->_name, SQLite::OPEN_READWRITE);

		  private:
			std::string _name;
			void		_create(std::string &name);
			bool		_file_exist(std::string file);
		};

	}// namespace storage
}// namespace sentinel
*/