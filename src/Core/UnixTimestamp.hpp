#pragma once
#include <chrono>
#include <string>

namespace Sentinel {

	class UnixTimestamp {
	  public:
		UnixTimestamp() {}

		operator UnixTimestamp() const {
			return UnixTimestamp(unix_timestamp_);
		}
		operator unsigned long long() const {
			return unix_timestamp_;
		}

		std::string to_string() const {
			return std::to_string(unix_timestamp_);
		};

		UnixTimestamp now() {
			unix_timestamp_ = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		}

	  private:
		UnixTimestamp(unsigned long long unix_timestamp) : unix_timestamp_(unix_timestamp) {}
		unsigned long long unix_timestamp_;
	};

}// namespace sentinel
