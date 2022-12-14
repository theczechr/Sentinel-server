#pragma once
#include <drogon/utils/Utilities.h>

namespace sentinel {
	namespace utils {

		class UUID {
		  public:
			UUID() {}
			UUID(std::string UUID) : UUID_(UUID) {}

			operator UUID() const {
				return UUID(UUID_);
			}
			operator std::string() const {
				return UUID_;
			}

			UUID generage_new() {
				return UUID_ = drogon::utils::getUuid();
			}

		  private:
			std::string UUID_;
		};

	}// namespace utils
}// namespace sentinel
