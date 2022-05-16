#include <iostream>
#include <regex>

#include <nlohmann/json.hpp>

#include "../vendor/aixlog.hpp"

#include "account.hpp"
#include "hashing.hpp"
#include "utils.hpp"

bool Account::valid_username(const std::string& username)
{
	if (!((username.length() >= 3)
		&& (username.length() <= 20)))
	{
		return false;
	}

	// to check space
	if (username.find(' ') != std::string::npos)
	{
		return false;
	}

	if constexpr (true)
	{
		int count = 0;

		// check digits from 0 to 9
		for (int i = 0; i <= 9; i++)
		{
			// to convert int to string
			std::string str1 = std::to_string(i);

			if (username.find(str1) != std::string::npos)
			{
				count = 1;
			}
		}
		if (count == 0)
		{
			return false;
		}
	}

	// for special characters
	if (!(username.find('@') != std::string::npos || username.find('#') != std::string::npos
		|| username.find('!') != std::string::npos || username.find('~') != std::string::npos
		|| username.find('$') != std::string::npos || username.find('%') != std::string::npos
		|| username.find('^') != std::string::npos || username.find('&') != std::string::npos
		|| username.find('*') != std::string::npos || username.find('(') != std::string::npos
		|| username.find(')') != std::string::npos || username.find('-') != std::string::npos
		|| username.find('+') != std::string::npos || username.find('/') != std::string::npos
		|| username.find(':') != std::string::npos || username.find('.') != std::string::npos
		|| username.find(', ') != std::string::npos || username.find('<') != std::string::npos
		|| username.find('>') != std::string::npos || username.find('?') != std::string::npos
		|| username.find('|') != std::string::npos))
	{
		return false;
	}

	if constexpr (true)
	{
		int count = 0;

		// checking capital letters
		for (int i = 65; i <= 90; i++)
		{
			// type casting
			char c = static_cast<char>(i);

			std::string str1 = std::to_string(c);
			if (username.find(str1) != std::string::npos)
			{
				count = 1;
			}
		}
		if (count == 0)
		{
			return false;
		}
	}

	if constexpr (true)
	{
		int count = 0;

		// checking small letters
		for (int i = 97; i <= 122; i++)
		{
			// type casting
			char c = static_cast<char>(i);
			std::string str1 = std::to_string(c);

			if (username.find(str1) != std::string::npos)
			{
				count = 1;
			}
		}
		if (count == 0)
		{
			return false;
		}
	}

	// if all conditions fails
	return true;
}

bool Account::valid_email(const std::string& email) const
// Maybe rewrite it ?
{
	const std::regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
	// Tohle se mi nelibi.. je to quick solution. Byl bych radsi kdybychom to udelali my, ale treba se pletu. Musime se o tom pobavit
	// musime zde dodelat kontrolu zda uz email neexistuje, bud dodelame az s databazi, nebo zatim jen jako proof of concept v jsonu

	return std::regex_match(email, pattern);
}

bool Account::valid_password(const std::string& password)
{
	constexpr char allowed_chars[] = {
		'`', '~', '!', '@', '#', '$', '%', '^', '&', '*',
		'(', ')', '-', '_', '+', '=', '[', ']', ';', ':',
		'\'', '\"', '<', '>', ',', '.', '/', '?'
	};

	for (const char c : password)
	{
		if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || password == allowed_chars)
		// password == allowed_chars - stale musime fixnout, domluvime se jeste

		{
			if (password.length() >= 12 && password.length() <= 45) // Check correct password length
			{
				LOG(ERROR) << "ERROR: " << "Password is correct.";

				return true;
			}

			LOG(ERROR) << "ERROR: " << "Password is too short or long.";

			return false;
		}

		LOG(ERROR) << "ERROR: " << "Password contains forbidden characters.";
	}

	return false;
}

bool Account::valid_number(int phone_number)
{
	// Somehow check it

	return false;
}

void Account::create(const std::string& username, const std::string& email, const std::string& password,
                     int phone_number)
{
	std::string key_email;
	std::string client_email;
	nlohmann::json loaded_accounts;

	LOG(INFO) << "INFO: " << "Create your account!";

	hashed_username = hash(std::string("username"));
	hashed_password = hash(std::string("password", 4, 40));
	hashed_email = hash(std::string("email"));
	hashed_phone_number = hash(std::string("phone-number"));
	key_email = std::to_string(client_id(client_email));

	// Check if email already exist
	//std::string hashed_key = std::to_string(client_id(to_check));

	LOG(INFO) << "INFO: " << "Happened succesfully!";

	std::ifstream clients("clients.json"); // first we read the database
	if (!clients || utils::file_empty(clients)) // check if file is empty
	{
		LOG(ERROR) << "ERROR: " << "File is empty or couldn't be opened.";

		clients.close();
	}
	else
	{
		clients >> loaded_accounts; // and set it as "loaded_accounts"
		clients.close();
	}

	loaded_accounts[key_email] = {
		{"username", username}, {"password", password}, {"email", email}, {"phone-number", phone_number}
	}; // then append the new account to it with the key "email"
	std::ofstream write("clients.json");

	write << loaded_accounts; // save to the file again with new account
	write.close();
}

void Account::login(const std::string& username, std::string email, std::string password, int phone_number) const
{
	std::string key_email;

	nlohmann::json loaded_accounts;

	std::ifstream file("clients.json");
	file >> loaded_accounts;
	file.close();

	for (size_t num_of_tries = 3; num_of_tries > 0; --num_of_tries)
	{
		std::cout << "You have " << num_of_tries << " tries." << std::endl;

		std::cout << "Enter your email: ";
		std::cin >> email;

		std::cout << "Enter your password: ";
		std::cin >> password;

		size_t l_hashed_email = client_id(email);
		size_t l_hashed_password = hash(password);

		key_email = std::to_string(l_hashed_email);

		for (auto it = loaded_accounts.begin(); it != loaded_accounts.end(); ++it) //looping through the json keys
		{
			if (it.key() == key_email) // find the email
			{
				nlohmann::json value = it.value(); // creating a json from the keys
				for (auto val = value.begin(); val != value.end(); ++val) //looping through the json keys
				{
					if (val.key() == "password" && val.value() == l_hashed_password)
						// checking if the password is correct
					LOG(INFO) << "INFO: " << "Logged in!";
				}

				LOG(ERROR) << "ERROR: " << "Incorrect password.";
				break;
			}
		}

		LOG(ERROR) << "ERROR: " << "This account doesn't exist.";
	}

	LOG(ERROR) << "ERROR: " << "You have failed to log in.";
}
