#pragma once 

# include "transform.hpp"
# include <iostream>
# include <concepts>
# include <functional>

# define COM_COLOR "\033[1;34m"
# define WARNING_COLOR "\033[1;31m"
# define ERROR_COLOR "\033[38;5;1m"
# define DEF_COLOR "\033[0m"
# define OK_COLOR "\033[32m"

inline constexpr const char * DEFAULT_WORD = "Cicada3301";

template <typename T>
concept	JsonType = requires(T t)
{
	typename	T::value_type;
} && std::same_as<typename T::value_type, json>;

class Registration
{
public:
	Registration() = default;
	~Registration() = default;
public:
	template <JsonType Container>
	void	set_username(Container& list
			, std::ostream& out = std::cout
			, std::istream& in = std::cin)
	{
		std::string	data;
		
		do
		{
			out << COM_COLOR << "Enter Username: " << DEF_COLOR;
			in.clear();
			in >> data;
			if (data.empty())
			{
				out << WARNING_COLOR << "Input empty.Try again!." << DEF_COLOR << std::endl;
				continue;
			}
			else if (std::any_of(list.cbegin()
					, list.cend()
					, [&](const json& obj) { return (obj.contains(USERNAME)
									&& obj[USERNAME] == data);}))
			{
				out << WARNING_COLOR << "Name is busy!." << DEF_COLOR << std::endl;
				continue;
			}
			else
			{
				m_new_user.set_username(data);
				return ;
			}
		} while (true);
	}

	void	set_password(std::ostream& out = std::cout
			, std::istream& in = std::cin
			, std::function <bool(const std::string&)> password_criteri = default_criteri)
	{
		std::string	password;
		
		do
		{
			out << COM_COLOR << "Enter password: " << DEF_COLOR;
			in.clear();
			in >> password;
			if (password_criteri(password))
			{
				m_new_user.change_password(password);
				break ;
			}
			else
			{
				out << WARNING_COLOR << "Insecure pasword!." << DEF_COLOR << std::endl;
				continue;
			}
		} while (true);
	};

	bool	repeat_password(std::ostream& out = std::cout, std::istream& in = std::cin);
	void	set_secret_word(std::ostream& out = std::cout, std::istream& in = std::cin);
	inline Account	get_new_account(void) const noexcept {return (m_new_user);}
private:
	Account	m_new_user;
};

class SignIn
{
public:
	SignIn() = default;
	~SignIn() = default;
public :
	template <JsonType Container>
	bool	find_user(Container& list, const std::string& name, std::ostream& out = std::cout)
	{
		for (auto account: list)
			if(account.contains(KEY1))
			{
				toDecode.set_CalcCoeff(account[KEY1]);
				if (account.contains(USERNAME) && toDecode(account[USERNAME]) == name)
					return (m_user = deserializeFromJson(account), true);
	     		}
		out << ERROR_COLOR << "Undefined username!." << DEF_COLOR << std::endl;
		return (false);
	}

	bool	forgot_password(std::ostream& out = std::cout
			, std::istream& in = std::cin
			, std::function <bool(const std::string&)> password_criteri = default_criteri)
	{
		std::string data;

		out << COM_COLOR << "Enter secret word: " << DEF_COLOR;
		in.clear();
		in >> data;
		if (m_user.check_word(data))
		{
			out << OK_COLOR << "\nGood! Now please enter new password:"  << DEF_COLOR;
			in.clear();
			in >> data;
			if (password_criteri(data))
				return (m_user.change_password(data), true);
			else
				return (out << WARNING_COLOR << "Insecure pasword!."
						<< DEF_COLOR << std::endl,
					false);
		}	
		else
			return (out << ERROR_COLOR <<"Wrong Secret Word !."
				       << DEF_COLOR << std::endl, false);
	};

	bool	change_password(std::ostream& out = std::cout
			, std::istream& in = std::cin
			, std::function <bool(const std::string&)> password_criteri = default_criteri)
	{
		std::string	data;

		out << COM_COLOR << "Enter password: " << DEF_COLOR;
		in.clear();;
		in >> data;
		if (m_user.check_password(data))
		{
			out << COM_COLOR << "Enter new password: " << DEF_COLOR;
			in.clear();
			in >> data;
			if (password_criteri(data))
				return (m_user.change_password(data), true);
			else
				out << WARNING_COLOR << "Insecure password!." << DEF_COLOR << std::endl;
		}
		else
			out << ERROR_COLOR <<"Wrong password!." << DEF_COLOR << std::endl;
		return (false);
	};

	template <JsonType Container>
	bool	save_changes(Container& list)
	{
		for (auto user_json: list)
		{
			if (user_json.contains(KEY1))
			{
				toDecode.set_CalcCoeff(user_json[KEY1]);
				if (user_json.contains(USERNAME)
					&& toDecode(user_json[USERNAME]) == m_user.get_username())
					return (user_json = makeJson(m_user), true);
			}
			else
				break ;
		}
		return (false);
	};
	inline bool	check_password(const std::string& passw) const noexcept
	{return (m_user.check_password(passw));}
private:
	Account	m_user;
};
