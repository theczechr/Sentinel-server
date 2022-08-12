#pragma once
#include <drogon/utils/Utilities.h>

namespace Utils
{

class UUID
{
  public:
    UUID()
    {
    }
    UUID(std::string uuid) : m_UUID(uuid)
    {
    }

    UUID generage_new()
    {
        return m_UUID = drogon::utils::getUuid();
    }
    operator UUID() const
    {
        return UUID(m_UUID);
    }
    operator std::string() const
    {
        return m_UUID;
    }

  private:
    std::string m_UUID;
};

} // namespace Utils
