#include "../vendor/aixlog.hpp"

#include "menu.hpp"
#include "account.hpp"

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
	std::string email;
	std::string password;
	std::string phone_number;

	LOG(INFO) << "INFO: " << "* - required\n";
	std::cout << "Enter username*: \n";
	std::cin >> username;
	std::cout << "Enter email: \n";
	std::cin >> email;
	std::cout << "Enter password*: \n";
	std::cin >> password;
	std::cout << "Enter phone number: \n";
	std::cin >> phone_number;

	a.create(username, email, password, phone_number);
}

void menu::login()
{
	constexpr Account a{};

	std::string username;
	std::string email;
	std::string password;
	std::string phone_number;

	LOG(ERROR) << "ERROR: " << "Leave blank if none\n";
	std::cout << "Enter username: \n";
	std::cin >> username;
	std::cout << "Enter email: \n";
	std::cin >> email;
	std::cout << "Enter password: \n";
	std::cin >> password;
	std::cout << "Enter phone number: \n";
	std::cin >> phone_number;

	a.login(username, email, password, phone_number);
}
