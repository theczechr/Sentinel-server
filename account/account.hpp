#pragma once
class Account
{
	static bool valid_username(const std::string& username);
	bool valid_email(const std::string& email) const;
	static bool valid_password(const std::string& password);
	static bool valid_number(int phone_number);

	void change_username();
	void change_email();
	void change_password();
public:
	size_t hashed_email; // hashed?
	size_t hashed_username; // hashed?
	size_t hashed_password;
	size_t hashed_phone_number; // hashed?
	void create(const std::string& username, const std::string& email, const std::string& password, int phone_number);
	void login(const std::string& username, std::string email, std::string password, int phone_number) const;
	void close(); // Delete account
	void reopen(); // Only within x days ?
};

// Mozna zvlast funkce na registraci a v te funkci by se proste vytvarel Account
// Musime se o tom pobavit, ale podle me to bude lepsi
// Premyslel jsem nad tim vic a ztratil jsem se v tom
