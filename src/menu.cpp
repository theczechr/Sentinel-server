#include "accounts.h"
void menu() {
	int choice;
	bool choosing_path = true;
	while (choosing_path)
	{
		log("Bank system\n");
		log("Choose from the further options: ");
		log("1: Open an account");
		log("2: Login to an existing account");
		log("3: To be implemented soon!");
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
			log("Spatne cislo");
			choosing_path = false;
			break;
		}
	}
}