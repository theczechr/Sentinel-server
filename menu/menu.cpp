#include "../vendor/aixlog.hpp"

#include "menu.hpp"
#include "account.hpp"

// Chtel jsem aby jsme meli takhle rozdeleny to menu, ale rn to nefunguje.. Musime nejdriv poresit ty ucty a potom se vrhnem na tohle
// Update: Nejak jsem to fixnul, ale nefungujou ty accounts xDD
// Update: Register, login funkce se opakuje, ale podle me to je ok

void menu::start()
{
	int choice;
	bool choosing_path = true;

	while (choosing_path)
	{
		LOG(INFO) << "INFO: " << "[1] Login\n";
		LOG(INFO) << "INFO: " << "[2] Register\n";
		std::cin >> choice;

		switch (choice)
		{
		case 1:
			login();
			choosing_path = false;
			break;
		case 2:
			create();
			choosing_path = false;
			break;
		default:

			LOG(ERROR) << "ERROR: " << "Spatne cislo\n";

			choosing_path = false;
			break;
		}
	}
}

void menu::create()
{
	Account a{};

	std::string username;
	const std::string email;
	const std::string password;
	constexpr int phone_number = 0;

	LOG(INFO) << "INFO: " << "* - required\n";
	std::cout << "Enter username*: \n";
	std::cin >> username;
	std::cout << "Enter email: \n";
	std::cin >> username;
	std::cout << "Enter password*: \n";
	std::cin >> username;
	std::cout << "Enter phone number: \n";
	std::cin >> username;

	a.create(username, email, password, phone_number);
}

void menu::login()
{
	constexpr Account a{};

	std::string username;
	const std::string email;
	const std::string password;
	constexpr int phone_number = 0;

	LOG(ERROR) << "ERROR: " << "Leave blank if none\n";
	std::cout << "Enter username: \n";
	std::cin >> username;
	std::cout << "Enter email: \n";
	std::cin >> username;
	std::cout << "Enter password: \n";
	std::cin >> username;
	std::cout << "Enter phone number: \n";
	std::cin >> username;

	a.login(username, email, password, phone_number);
}
