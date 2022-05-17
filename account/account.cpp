#include <iostream>
#include <regex>

#include <nlohmann/json.hpp>

#include "../vendor/aixlog.hpp"

#include "account.hpp"
#include "hashing.hpp"
#include "utils.hpp"

/* Doesn't specify reason what's wrong, should be added (easy) */
bool Account::check_valid(const std::string& to_be_checked, const size_t string_from, const size_t string_to, const bool use_digits, const bool allow_special_char) const
{
	if (!(to_be_checked.length() >= string_from
		&& to_be_checked.length() <= string_to))
		return false;

	// to check space
	if (to_be_checked.find(' ') != std::string::npos)
		return false;

	int count = 0;

	if (use_digits)
	{
		// check digits from 0 to 9
		for (int i = 0; i <= 9; i++)
		{
			// to convert int to string
			std::string str1 = std::to_string(i);

			if (to_be_checked.find(str1) != std::string::npos)
				count = 1;
		}

		if (count == 0)
			return false;
	}


	// for special characters
	if (!allow_special_char)
	{
		std::string special_chars = "@#!~$%^&*()-_=+/\.,:?|<> ";

		for (char c : special_chars)
		{
			if (to_be_checked.find(c) != std::string::npos)
				return false;
		}
	}

	count = 0;

	// checking capital letters
	for (int i = 65; i <= 90; i++)
	{
		// type casting
		const char c = static_cast<char>(i);

		std::string str1 = std::to_string(c);
		if (to_be_checked.find(str1) != std::string::npos)
			count = 1;
	}

	if (count == 0)
		return false;

	count = 0;

	// checking small letters
	for (int i = 97; i <= 122; i++)
	{
		// type casting
		const char c = static_cast<char>(i);
		std::string str1 = std::to_string(c);

		if (to_be_checked.find(str1) != std::string::npos)
			count = 1;
	}

	if (count == 0)
		return false;

	return true;
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
