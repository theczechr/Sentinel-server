#include "account.hpp"

bool Account::valid_email(std::string email) // Maybe rewrite it ?
{
	const std::regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+"); // Tohle se mi nelibi.. je to quick solution. Byl bych radsi kdybychom to udelali my - musime se o tom pobavit

	return std::regex_match(email, pattern);
}

bool Account::valid_password(std::string password)
{
	char allowed_chars[] = {'`','~','!','@','#','$','%','^','&','*',
							'(',')','-','_','+','=','[',']',';',':',
							'\'','\"','<','>',',','.','/','?' };
	if ((password[0] >= 'a' && password[0] <= 'z') || (password[0] >= 'A' && password[0] <= 'Z') || (password == allowed_chars)) // password == allowed_chars - to nevim jestli funguje, ale ostatni by melo
	{
		if (password.length() >= 12 && password.length() <= 45) // Check correct password length
		{
			utils::clog("Password is correct.");
			return true;
		}
		else
		{
			utils::clog("Password is too short or long.");
			return false;
		}
	}
	else
	{
		utils::clog("Password contains forbidden characters.");
		return false;
	}
}

void Account::create()
{
	size_t username;
	size_t password;
	size_t email;
	int phone_number;

	std::string key_email;
	std::string client_email;
	nlohmann::json loaded_accounts;

	utils::cflush();
	utils::clog("Create your account!");

	username = hash(registration("username"));
	password = hash(registration("password", 4, 40));
	email = hash(registration("email"));
	phone_number = hash(registration("phone-number"));
	key_email = std::to_string(client_id(client_email));

	utils::clog("Happened succesfully!");
	std::ifstream clients("clients.json"); // first we read the database
	if (!clients || utils::is_file_empty(clients)) // check if file is empty
	{
		utils::clog("File is empty or couldn't be opened.");
		clients.close();
	}
	else
	{
		clients >> loaded_accounts; // and set it as "loaded_accounts"
		clients.close();
	}

	loaded_accounts[key_email] = { {"username", username}, {"password", password} , {"email", email}, {"phone-number", phone_number} }; // then append the new account to it with the key "email"
	std::ofstream write("clients.json");

	write << loaded_accounts; // save to the file again with new account
	write.close();
}

bool Account::control(std::string to_check, int min_length = 3, int max_length = 30) // Tohle potrebuje full rewrite. Snazil jsem se o to, ale jak to je vsechno propojeny tak jsem musel udelat zase neco jinyho a tak
{
	// Type:
	// 2 - email
	// 3 - password
	bool correct = true;
	nlohmann::json all_acounts;
	char allowed_chars[] = {'`','~','!','@','#','$','%','^','&','*',
							'(',')','-','_','+','=','[',']',';',':',
							'\'','\"','<','>',',','.','/','?'};
	std::string allowed_characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890"; // change to char array
	//if (type == 2)
	//{
	//	allowed_characters = allowed_characters + "@_-.";
	//}
	//else if (type == 3)
	//{
	//	allowed_characters = allowed_characters + "@_-.+=`;'[];,./|?<>:\"";
	//}

	if (to_check.length() >= min_length && to_check.length() <= max_length)  // checking correct word length
	{
		// Check if file exist
		std::ifstream clients("clients.json");
		if (!clients || utils::is_file_empty(clients))
		{
			utils::clog("File is empty or couldn't be opened.");
			clients.close();
			return false;
		}
		else
		{
			clients >> all_acounts;
			clients.close();
		}

		// Check if email already exist
		std::string hashed_key = std::to_string(client_id(to_check));
		for (auto it = all_acounts.begin(); it != all_acounts.end(); ++it) // looping through the json keys
		{
			if (it.key() == hashed_key) // if we find the email is already being used, we return false
			{
				utils::clog("There is already an account with this email");
				return false;
			}
		}

		// Check for chars
		for (size_t x = 0; x < to_check.length(); x++)
		{
			if (allowed_characters.find(to_check[x]) == std::string::npos) // checking if all characters are correct
			{
				utils::clog("There was an inccorect character");
				correct = false; // sets the correct variable false if there are any incorrect characters
			}
		}

		if (correct)  // checking if the word is correct, returns true if it is
		{
			utils::clog("All characters were correct");
			return true;
		}
	}
	return false; // returns false if the word is wrong
}

std::string Account::registration(std::string tag, int min_length = 3, int max_length = 30) // registraion
{
	bool correct = true;
	std::string to_control;
	while (correct) // remains true until the string to_control is correct
	{
		utils::clog("Use atleast 3 characters");
		std::cout << "Enter " << tag << ": ";
		std::cin >> to_control;
		if (control(to_control, min_length, max_length))
		{
			correct = false;
		}
	}
	utils::cflush();
	return to_control;
}

void Account::login()
{
	std::string email;
	std::string password;
	std::string key_email;
	nlohmann::json loaded_accounts;
	std::ifstream file("clients.json"); // first we read the database
	file >> loaded_accounts; // and set it as "loaded_accounts"
	file.close();
	for (size_t num_of_tries = 3; num_of_tries > 0; --num_of_tries)
	{
		std::cout << "You have " << num_of_tries << " tries." << std::endl;
		std::cout << "Enter your email: ";
		std::cin >> email;
		std::cout << "Enter your password: ";
		std::cin >> password;
		size_t hashed_email = client_id(email);
		size_t hashed_password = hash(password);
		key_email = std::to_string(hashed_email);

		for (auto it = loaded_accounts.begin(); it != loaded_accounts.end(); ++it) //looping through the json keys
		{
			if (it.key() == key_email) // find the email
			{
				nlohmann::json value = it.value(); // creating a json from the keys
				for (auto val = value.begin(); val != value.end(); ++val) //looping through the json keys
				{
					if (val.key() == "password" && val.value() == hashed_password) // checking if the password is correct
					{
						utils::clog("Logged in!");
					}
				}
				utils::clog("Incorrect password.");
				break;
			}
		}
		utils::clog("This account doesn't exist.");
	}
	utils::clog("You have failed to log in.");
}
