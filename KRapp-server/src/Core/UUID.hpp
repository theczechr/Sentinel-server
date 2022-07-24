#pragma once
#include <drogon/utils/Utilities.h>

namespace Core {
	class UUID
	{
	public:
		UUID() : m_UUID(drogon::utils::getUuid()) { }

		std::string to_string() const { return m_UUID; };
	private:
		std::string m_UUID;
	};
}