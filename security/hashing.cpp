#include "hashing.hpp"

size_t hash(const std::string& to_hash)
// advanced hashing func from std::hash, used for hashing everything except client ids
{
	const std::size_t str_hash = std::hash<std::string>{}(to_hash);

	return str_hash;
}
