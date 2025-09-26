#pragma once
#include <string>
#include <vector>

namespace sentinel {
namespace utils {

	std::vector<uint8_t> base64_decode(const std::string &input_base64);
	std::string base64_encode(const std::vector<uint8_t> &data);

} // namespace utils
} // namespace sentinel


