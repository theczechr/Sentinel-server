#pragma once
#include "UUID.hpp"
#include "UnixTimestamp.hpp"
#include "Username.hpp"

#include <cassert> // std::assert
#include <optional>// std::optional
#include <trantor/utils/Logger.h>

namespace Sentinel {

	class Account {
	  public:
		enum class Status {
			active	 = 0,
			inactive = 1
		};

		UUID get_uuid() const;
		void set_uuid(UUID uuid);

		Username get_username() const;
		void	 set_username(Username& username);

		std::string get_pub_key_fprint() const;
		void		set_pub_key_fprint(std::string pub_key_fprint);

		std::optional<std::string> get_recovery_phrase() const;
		void					   set_recovery_phrase(std::string recovery_phrase);

		Status get_status() const;
		void   set_status(Status status);

		UnixTimestamp get_last_login() const;
		void		  set_last_login(UnixTimestamp last_login);

	  private:
		UUID		  uuid_;
		Username	  username_;
		std::string	  pub_key_fprint_;
		bool		  recovery_enabled_ = true;
		std::string	  recovery_phrase_;
		Status		  status_ = Status::active;
		UnixTimestamp last_login_;

		void require_active_();
	};

}// namespace Sentinel
