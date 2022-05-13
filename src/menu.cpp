#include "menu.hpp"
#include "accounts.hpp"
#include "console.hpp"

void menu()
{
	int choice;
	bool choosing_path = true;
	Register R;
	while (choosing_path)
	{
		clog("AAAAAAAAAAAAAAAA\n");
		clog("Choose from the further options: ");
		clog("1: Open an account");
		clog("2: Login to an existing account");
		clog("3: To be implemented soon!");
		clog("Your choice:\n~");
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			R.create_account();
			choosing_path = false;
			break;

		case 2:
			R.login();
			choosing_path = false;
			break;

		default:
			clog("Spatne cislo");
			choosing_path = false;
			break;
		}
	}
}