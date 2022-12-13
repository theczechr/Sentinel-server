#pragma once
#include "Utils/UUID.hpp"

#include <optional>// std::optional
#include <trantor/utils/Logger.h>

namespace sentinel {

	class account {
	  public:
		utils::UUID get_uuid() const;
		void		set_uuid(utils::UUID uuid);

		std::string get_username() const;
		void		set_username(std::string username);

		std::string get_pub_key_fprint() const;
		void		set_pub_key_fprint(std::string pub_key_fprint);

		std::optional<std::string> get_recovery_phrase() const;
		void					   set_recovery_phrase(std::string recovery_phrase);

		bool get_status() const;
		void set_status(bool status);

		unsigned long long get_last_login() const;
		void			   set_last_login(unsigned long long last_login);

	  private:
		utils::UUID		   uuid_;
		std::string		   username_;
		std::string		   pub_key_fprint_;
		bool			   recovery_enabled_ = true;
		std::string		   recovery_phrase_;
		bool			   status_ = true;
		unsigned long long last_login_;

		void require_active();
	};

}// namespace sentinel
