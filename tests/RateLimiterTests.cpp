#include "Utils/RateLimiter.hpp"
#include <cassert>
#include <iostream>

int main() {
	sentinel::utils::RateLimiter rl(2, 60);
	assert(rl.allow("key"));
	assert(rl.allow("key"));
	assert(!rl.allow("key"));
	std::cout << "RateLimiterTests OK\n";
	return 0;
}

