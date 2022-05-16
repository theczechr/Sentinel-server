#pragma once
class Account
{
	void change_username();
	void change_email();
	void change_password();
public:
	size_t hashed_email;
	size_t hashed_username;
	size_t hashed_password;
	size_t hashed_phone_number;

	[[nodiscard]] bool check_valid(const std::string& to_be_checked, size_t string_from, size_t string_to, bool allow_special_char) const;
	void create(const std::string& username, const std::string& email, const std::string& password, int phone_number);
	void login(const std::string& username, std::string email, std::string password, int phone_number) const;
	void close(); // Delete account
	void reopen(); // Only within x days ?
};

// Mozna zvlast funkce na registraci a v te funkci by se proste vytvarel Account
// Musime se o tom pobavit, ale podle me to bude lepsi
// Premyslel jsem nad tim vic a ztratil jsem se v tom
