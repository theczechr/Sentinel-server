#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"
#include "Console.h"
#include "accounts.h"
#include "hashing.h"
using namespace nlohmann;


bool is_empty(std::ifstream& pFile)
{
	return pFile.peek() == std::ifstream::traits_type::eof();
}

bool control(std::string to_check, int type, int min_length = 3, int max_length = 30) {
	bool correct = true;
	json all_acounts;
	std::string allowed_characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
	if (type == 2) {
		allowed_characters = allowed_characters + "@_-.";
	}
	else if (type == 3) {
		allowed_characters = allowed_characters + "@_-.+=`;'[];,./|?<>:\"";
	}

	if ( to_check.length() >= min_length && to_check.length() <= max_length)  //checking correct word length
	{

		if (type == 2)
		{
			std::ifstream myfile("clients.json");
			myfile >> all_acounts;
			myfile.close();
			std::string hashed_key = std::to_string(client_id(to_check));
			for (auto it = all_acounts.begin(); it != all_acounts.end(); ++it) //looping through the json keys
			{
				if (it.key() == hashed_key) // if we find the email is already being used, we return false
				{
					log("There is already an account with this email");
					return false;
				}
			}
		}

		for (size_t x = 0; x < to_check.length(); x++) {
			if (allowed_characters.find(to_check[x]) == std::string::npos) // checking if all characters are correct
			{
				log("There was an inccorect character");
				correct = false; // sets the correct variable false if there are any incorrect characters
			}
		}
		if (correct)  // checking if the word is correct, returns true if it is
		{
			log("All characters were correct");
			return true;
		}
	}
	return false; // returns false if the word is wrong
}

std::string registration(std::string tag, int type, int min_length = 3, int max_length = 30) // registraion
{
	bool correct = true;
	std::string to_control;
	while (correct) // remains true until the string to_control is correct
	{
		log("Use atleast 3 characters");
		std::cout << "Enter " << tag << ": ";
		std::cin >> to_control;
		if (control(to_control, type, min_length, max_length)) {
			correct = false;
		}
	}


	flush();
	return to_control;
}

void createAccount() {
	size_t name, surname, email, password;
	std::string key_email, client_email;
	bool boolname = true, boolsurname = true, boolemail = true, boolpassword = true;
	json loaded_accounts;

	flush();
	log("Create your account!");

	name = hash(registration("name", 0));
	surname = hash(registration("surname", 1));
	client_email = registration("email", 2);
	password = hash(registration("password", 3, 3, 40));
	email = hash(client_email);
	key_email = std::to_string(client_id(client_email));



	std::ifstream myfile("clients.json"); // first we read the database
	if (!myfile || is_empty(myfile))
	{
		log("File is empty or couldn't be opened.");
	}
	else
	{
		myfile >> loaded_accounts; // and set it as "loaded_accounts"
		myfile.close();
	}
	

	loaded_accounts[key_email] = { {"name", name}, {"surname", surname}, {"email", email}, {"passw", password} }; // then append the new account to it with the key "email"
	std::ofstream write("clients.json");

	write << loaded_accounts; // save to the file again with new account
	write.close();
}

bool logincontrol()
{
	std::string email, password, key_email;
	json loaded_accounts;
	std::ifstream file("clients.json"); // first we read the database
	file >> loaded_accounts; // and set it as "loaded_accounts"
	file.close();
	for (size_t num_of_tries = 3; num_of_tries > 0; --num_of_tries ) {
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
				json value = it.value(); // creating a json from the keys
				for (auto val = value.begin(); val != value.end(); ++val) //looping through the json keys
				{
					if (val.key() == "passw" && val.value() == hashed_password) // checking if the password is correct
					{
						return true;
					}
				}
				log("Incorrect password.");
				break;
			}
		}
		log("This account doesn't exist.");
	}
	log("You have failed to log in.");
	return false;
}

void login() { 
	if (logincontrol()) {
		log("Logged in!");
	}
}