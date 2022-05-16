#include "hashing.hpp"

size_t hash(const std::string& to_hash) // advanced hashing func from std::hash, used for hashing everything except client ids
{
	const std::size_t str_hash = std::hash<std::string>{}(to_hash);

	return str_hash;
}

size_t client_id(const std::string& email) // basic hashing func, used for making client ids
{
	size_t user_id = 0;
	constexpr int number = 5;

	for (size_t i = 0; i < email.length(); i++)
		user_id = user_id + (pow(number, i) * sqrt(static_cast<size_t>(email[i])));

	return user_id;
}
