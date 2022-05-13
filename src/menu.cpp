#include "menu.h"
#include "accounts.h"
#include "console.h"

void menu() {
	int choice;
	bool choosing_path = true;
	while (choosing_path)
	{
		clog("Bank system\n");
		clog("Choose from the further options: ");
		clog("1: Open an account");
		clog("2: Login to an existing account");
		clog("3: To be implemented soon!");
		std::cout << "Your choice:" << "\n" << "~ ";
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			createAccount();
			choosing_path = false;
			break;

		case 2:
			login();
			choosing_path = false;
			break;

		default:
			clog("Spatne cislo");
			choosing_path = false;
			break;
		}
	}
}