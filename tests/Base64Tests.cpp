#include "Utils/Base64.hpp"
#include <cassert>
#include <iostream>

int main() {
	std::vector<uint8_t> data = {'t','e','s','t'};
	std::string b64 = sentinel::utils::base64_encode(data);
	auto decoded = sentinel::utils::base64_decode(b64);
	assert(decoded == data);
	std::cout << "Base64Tests OK\n";
	return 0;
}

