#include "menu.hpp"

#include "account.hpp"
#include "utils.hpp"

// Chtel jsem aby jsme meli takhle rozdeleny to menu, ale rn to nefunguje.. Musime nejdriv poresit ty ucty a potom se vrhnem na tohle
// Update: Nejak jsem to fixnul, ale nefungujou ty accounts xDD
// Update: Register, login funkce se opakuje, ale podle me to je ok

void menu::start_menu()
{
	int choice;
	bool choosing_path = true;
	while (choosing_path)
	{
		utils::clog("[1] Login");
		utils::clog("[2] Register");
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			login_menu();
			choosing_path = false;
			break;

		case 2:
			register_menu();
			choosing_path = false;
			break;

		default:
			utils::clog("Spatne cislo");
			choosing_path = false;
			break;
		}
	}
}

void menu::register_menu()
{
	Account a{};

	std::string username;
	const std::string email;
	const std::string password;
	constexpr int phone_number = 0;

	utils::clog("* - required");
	std::cout << "Enter username*: "; std::cin >> username;
	std::cout << "Enter email: "; std::cin >> username;
	std::cout << "Enter password*: "; std::cin >> username;
	std::cout << "Enter phone number: "; std::cin >> username;

	a.create(username, email, password, phone_number);

	utils::cflush();
}

void menu::login_menu()
{
	Account a{};

	std::string username;
	const std::string email;
	const std::string password;
	constexpr int phone_number = 0;

	utils::clog("Leave blank if none");
	std::cout << "Enter username: "; std::cin >> username;
	std::cout << "Enter email: "; std::cin >> username;
	std::cout << "Enter password: "; std::cin >> username;
	std::cout << "Enter phone number: "; std::cin >> username;

	a.login(username, email, password, phone_number);

	utils::cflush();
}