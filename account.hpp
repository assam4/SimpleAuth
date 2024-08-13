#pragma once
#include "constants.h"

class Account
{
public : 
		Account() = default;
		Account(const std::string& name, const std::string& password, const std::string secretw)
			:	m_username(name),
				m_password(password),
				m_secret_word(secretw)
		{ }
		~Account() = default;
public :
		inline void set_username(const std::string& name) noexcept { m_username = name; }
		inline bool check_password(const std::string& attempt) const noexcept{ return m_password == attempt; }
		inline void change_password(const std::string& newpassword ) { m_password = newpassword; }
		inline bool check_secretword(const std::string& attempt) const noexcept{ return m_secret_word == attempt; }
		inline void change_secretword(const std::string& newword) { m_secret_word = newword;}
		inline std::string get_username() const { return m_username; }
		inline std::string get_password() const { return m_password; }
		inline std::string get_secretword() const { return m_secret_word; }
private :
	std::string m_username;
	std::string m_password;
	std::string m_secret_word;
};

