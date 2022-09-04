#pragma once
#include <chrono>
#include <string>

namespace Utils {// Dal bych to do jineho ns (UUID taky)

	class UNIX_TS {
	  public:
		UNIX_TS()
			: m_unix_ts(
				  std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch())
					  .count()) {};

		std::string to_string() const {
			return std::to_string(m_unix_ts);
		};

	  private:
		long long m_unix_ts;
	};

}// namespace Utils
