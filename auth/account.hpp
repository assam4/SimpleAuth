#pragma once

class Account
{
public: 
	Account() = default;
	Account(const std::string& name, const std::string& pwd, const std::string s_word)
	: m_username(name)
	, m_password(pwd)
	, m_secret_word(s_word)
	{ }
	~Account() = default;
public:
	inline void	set_username(const std::string& name) noexcept {m_username = name;}
	inline bool	check_password(const std::string& pwd) const noexcept {return (m_password == pwd);}
	inline void	change_password(const std::string& new_pwd ) {m_password = new_pwd;}
	inline bool	check_word(const std::string& word) const noexcept {return (m_secret_word == word);}
	inline void	change_word(const std::string& new_word) {m_secret_word = new_word;}
	inline std::string	get_username(void) const {return (m_username);}
	inline std::string	get_password(void) const {return (m_password);}
	inline std::string	get_secretword(void) const {return (m_secret_word);}
private:
	std::string m_username;
	std::string m_password;
	std::string m_secret_word;
};
