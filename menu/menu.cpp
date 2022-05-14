#include "menu.hpp"
#include "account.hpp"
#include "utils.hpp"

void menu()
{
	int choice;
	bool choosing_path = true;
	Account A;
	while (choosing_path)
	{
		utils::clog("[1] - Open an account");
		utils::clog("[2] - Login to an existing account");
		utils::clog("----");
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			A.create();
			choosing_path = false;
			break;

		case 2:
			A.login();
			choosing_path = false;
			break;

		default:
			utils::clog("Spatne cislo");
			choosing_path = false;
			break;
		}
	}
}