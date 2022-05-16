#include <iostream>
#include <regex>

#include <nlohmann/json.hpp>

#include "hashing.hpp"
#include "utils.hpp"
#include "account.hpp"

bool Account::valid_username(const std::string& username)
{
	const char allowed_chars[] = { '`','~','!','@','#','$','%','^','&','*',
						'(',')','-','_','+','=','[',']',';',':',
						'\'','\"','<','>',',','.','/','?' };

	if ((username[0] >= 'a' && username[0] <= 'z') || (username[0] >= 'A' && username[0] <= 'Z') || (username == allowed_chars)) // username == allowed_chars - to nevim jestli funguje, ale ostatni by melo
	{
		if (username.length() >= 3 && username.length() <= 20) // Check correct username length
		{
			utils::clog("Password is correct.");

			return true;
		}

		utils::clog("Username is too short or long.");

		return false;
	}

	utils::clog("Username contains forbidden characters.");

	return false;
}

bool Account::valid_email(const std::string& email) const
// Maybe rewrite it ?
{
	const std::regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+"); // Tohle se mi nelibi.. je to quick solution. Byl bych radsi kdybychom to udelali my, ale treba se pletu. Musime se o tom pobavit
	// musime zde dodelat kontrolu zda uz email neexistuje, bud dodelame az s databazi, nebo zatim jen jako proof of concept v jsonu

	return std::regex_match(email, pattern);
}

bool Account::valid_password(const std::string& password)
{
	const char allowed_chars[] = { '`','~','!','@','#','$','%','^','&','*',
							'(',')','-','_','+','=','[',']',';',':',
							'\'','\"','<','>',',','.','/','?' };

	for (const char c : password)
	{
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (password == allowed_chars)) // password == allowed_chars - stale musime fixnout, domluvime se jeste

		{
			if (password.length() >= 12 && password.length() <= 45) // Check correct password length
			{
				utils::clog("Password is correct.");

				return true;
			}

			utils::clog("Password is too short or long.");

			return false;
		}

		utils::clog("Password contains forbidden characters.");

		return false;
	}
}

bool Account::valid_number(int phone_number)
{
	// Somehow check it

	return false;
}

void Account::create(const std::string& t_username, const std::string& t_email, const std::string& t_password, int t_phone_number) // t = temporary, conflicting variable names with public variables in account.hpp
{
	std::string key_email;
	std::string client_email;
	nlohmann::json loaded_accounts;

	utils::cflush();
	utils::clog("Create your account!");

	hashed_username = hash(registration("username"));
	hashed_password = hash(registration("password", 4, 40));
	hashed_email = hash(registration("email"));
	phone_number = hash(registration("phone-number"));
	key_email = std::to_string(client_id(client_email));

	// Check if email already exist
	//std::string hashed_key = std::to_string(client_id(to_check));


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

void Account::login(const std::string& username, std::string email, std::string password, int phone_number) const
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
						utils::clog("Logged in!");

				}

				utils::clog("Incorrect password.");
				break;
			}
		}

		utils::clog("This account doesn't exist.");
	}

	utils::clog("You have failed to log in.");
}
