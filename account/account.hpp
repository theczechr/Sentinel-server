#pragma once
class Account
{
private:
	void change_username();
	void change_email();
	void change_password();
public:
	size_t hashed_email;
	size_t hashed_username;
	size_t hashed_password;
	size_t hashed_phone_number;

	[[nodiscard]] bool check_valid(const std::string& to_be_checked, size_t string_from, size_t string_to, bool use_digits, bool allow_special_char, const bool char_check) const;
	void create(const std::string& username, const std::string& email, const std::string& password, const std::string& phone_number);
	void login(const std::string& username, std::string email, std::string password, const std::string& phone_number) const;
	void close(); // Delete account
	void reopen(); // Only within x days ?
};
