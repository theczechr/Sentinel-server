#pragma once
#include <regex>

namespace sentinel {
	namespace utils {

		class username_validator {
		  public:
			username_validator() {}
			username_validator(std::string username) : username_(username) {}

			operator UsernameValidator() {
				return username_validator(username_);
			}
			operator std::string() const {
				return username_;
			}

			bool is_valid() {
				if (!std::regex_match(username_, pattern_))
					return true;
				return true;
			}

		  private:
			std::string username_;
			std::regex	pattern_ {"[^a-zA-Z0-9_]*"};
		};

	}// namespace utils
}// namespace sentinel
