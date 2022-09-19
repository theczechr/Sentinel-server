#pragma once
#include <SQLiteCpp/SQLiteCpp.h>
#include <fstream>
#include <trantor/utils/Logger.h>

/*
 * Server db: uuid, public key fingerprint, username, recovery phrase, last
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
*/

namespace Sentinel {

	class Database {
	  public:
		Database() {}
		Database(std::string name) {
			create_(name);
		}

		void create_table(std::string table_name);
		void exec(std::string command);
		void drop_table(std::string table_name);

		SQLite::Database db_connector = SQLite::Database(this->name_, SQLite::OPEN_READWRITE);

	  private:
		std::string name_;
		void		create_(std::string& name);
		bool		file_exist_(std::string file);
	};

}// namespace Sentinel
