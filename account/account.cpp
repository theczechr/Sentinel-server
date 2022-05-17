#include <iostream>
#include <regex>

#include <nlohmann/json.hpp>

#include "../vendor/aixlog.hpp"

#include "account.hpp"
#include "hashing.hpp"
#include "utils.hpp"

/* Doesn't specify reason what's wrong, should be added (easy) */
bool Account::check_valid(const std::string& to_be_checked, const size_t length_from, const size_t length_to, const bool digits, const bool special_char, const bool char_size) const
{
	if (!(to_be_checked.length() >= length_from
		&& to_be_checked.length() <= length_to))
		return false;

	// to check space
	if (to_be_checked.find(' ') != std::string::npos)
		return false;

	int count = 0;

	if (digits)
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
	if (!special_char)
	{
		std::string special_chars = "@#!~$%^&*()-_=+/\.,:?|<> ";

		for (char c : special_chars)
		{
			if (to_be_checked.find(c) != std::string::npos)
				return false;
		}
	}


	if (char_size)
	{
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
	}
	return true;
}

void Account::create(const std::string& username, const std::string& email, const std::string& password, const std::string& phone_number)
{
	std::string user_id;
	nlohmann::json loaded_accounts;

	LOG(INFO) << "INFO: " << "Create your account!";
	if (check_valid(username, 1, 50, false, false, false)
		&& check_valid(email, 5, 50, false, true, false)
		&& check_valid(password, 12, 50, true, true, true) 
		&& check_valid(phone_number, 9, 10, true, false, false))
	{
		hashed_username = hash(username);
		hashed_password = hash(password);
		hashed_email = hash(email);
		hashed_phone_number = hash(phone_number);
		user_id = std::to_string(hashed_username);

		// Check if username already exists with SQLite

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

		loaded_accounts[user_id] = {
			{"username", hashed_username}, {"password", hashed_password}, {"email", hashed_email}, {"phone-number", hashed_phone_number}
		}; // then append the new account to it with the key "email"
		std::ofstream write("clients.json");

		write << loaded_accounts; // save to the file again with new account
		write.close();
	}
	else LOG(INFO) << "INFO: " << "Failed!";
}

void Account::login(const std::string& username, std::string password) const
{
	std::string username_key;

	nlohmann::json loaded_accounts;

	std::ifstream clients("clients.json");
	if (!clients || utils::file_empty(clients)) // check if file is empty
	{
		LOG(ERROR) << "ERROR: " << "File is empty or couldn't be opened.";
		clients.close();
		return;
	}
	else
	{
		clients >> loaded_accounts; // and set it as "loaded_accounts"
		clients.close();
	}

	size_t l_hashed_username = hash(username);
	size_t l_hashed_password = hash(password);

	username_key = std::to_string(l_hashed_username);

	for (auto it = loaded_accounts.begin(); it != loaded_accounts.end(); ++it) //looping through the json keys
	{
		if (it.key() == username_key) // find the email
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
	LOG(ERROR) << "ERROR: " << "You have failed to log in.";
}
