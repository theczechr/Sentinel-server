#include <string>
#include <regex>

namespace Sentinel {

	class Username {
	  public:
		Username() {}
		Username(std::string username) : username_(username) {};

		operator Username() const {
			return Username(username_);
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
		std::regex	pattern_ {""};// TODO: Create pattern
	};

}// namespace sentinel
