#pragma once
#include <chrono>
#include <string>

namespace sentinel {
	namespace utils {

		class unix_timestamp {
		  public:
			unix_timestamp() {}

			operator unix_timestamp() const {
				return unix_timestamp(timestamp_);
			}
			operator unsigned long long() const {
				return timestamp_;
			}

			std::string to_string() const {
				return std::to_string(timestamp_);
			};

			unix_timestamp now() {
				timestamp_ = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
			}

		  private:
			unix_timestamp(unsigned long long timestamp) : timestamp_(timestamp) {}
			unsigned long long timestamp_;
		};

	}// namespace utils
}// namespace sentinel
