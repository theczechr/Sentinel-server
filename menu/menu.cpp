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
		utils::clog("[1] - Login");
		utils::clog("[2] - Register");
		utils::clog("----");
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			A.login();
			choosing_path = false;
			break;

		case 2:
			A.create();
			choosing_path = false;
			break;

		default:
			utils::clog("Spatne cislo");
			choosing_path = false;
			break;
		}
	}
}