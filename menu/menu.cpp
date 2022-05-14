#include "menu.hpp"

// Chtel jsem aby jsme meli takhle rozdeleny to menu, ale rn to nefunguje.. Musime nejdriv poresit ty ucty a potom se vrhnem na tohle

void menu::start_menu()
{
	int choice;
	bool choosing_path = true;
	while (choosing_path)
	{
		utils::clog("[1] - Login");
		utils::clog("[2] - Register");
		utils::clog("----");
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			menu::login_menu();
			choosing_path = false;
			break;

		case 2:
			//menu::register_menu();
			choosing_path = false;
			break;

		default:
			utils::clog("Spatne cislo");
			choosing_path = false;
			break;
		}
	}
}

void menu::register_menu(std::string tag) // Chtel jsem sem dat i registration funkci z account, ale ted me nenapada jak to udelat
{
	bool correct = true;
	std::string to_control;
	while (correct)
	{
		std::cout << "Enter " << tag << ": ";
		std::cin >> to_control;
	}
	utils::cflush();
}

void menu::login_menu()
{

}