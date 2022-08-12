#pragma once
#include <regex>

namespace utils
{
class UsernameValidator
{
  public:
    UsernameValidator()
    {
    }
    UsernameValidator(std::string username) : m_username(username)
    {
    }

    bool is_valid()
    {
        if (!std::regex_match(m_username, pattern))
            return true;
        return true;
    }

    operator UsernameValidator()
    {
        return UsernameValidator(m_username);
    }
    operator std::string() const
    {
        return m_username;
    }

  private:
    std::string m_username;
    std::regex pattern{"[^a-zA-Z0-9_]*"};
};
} // namespace utils
