#pragma once 
#include "transform.hpp"
#include <iostream>
#include <concepts>
#include <functional>

template <typename T>   // using concept to determine type
concept JsonType = requires(T t)
{
	typename T::value_type;
	std::same_as<typename T::value_type, json>;
};

class Registration
{
public :
		Registration() = default;
		~Registration() = default;
public :
		template <JsonType Container>
		void set_username(Container& list, std::ostream& out = std::cout, std::istream& in = std::cin)
		{
				std::string data;
			do 
			{
				out << "Please Enter Your Name: ";
				in.clear();
				in >> data;
				if (data.empty())
					{
						out << "Name cant be empty" << std::endl;
						continue;
					}
				else if (std::any_of(list.cbegin(), list.cend(),
					[&](const json& obj) { return obj.contains(USERNAME) && obj[USERNAME] == data;}))
					{
						out << "Name is busy. Choose another!" << std::endl;
						continue;
					}
				else 
					{
						m_new_user.set_username(data);
						return;
					}
			} while (true);
		}
		void set_password(std::ostream& out = std::cout, std::istream& in = std::cin, std::function <bool(const std::string&)> password_criteri = default_criteri)
		{
			std::string password;
			do
			{
				out << "Please enter your password: ";
				in.clear();
				in >> password;
				if (password_criteri(password))
					{
						m_new_user.change_password(password);
						return;
					}
				else
					{
						out << "Your password is too easy " << std::endl;
						continue;
					}
			} while (true);
		};
		bool repeat_password(std::ostream& out = std::cout, std::istream& in = std::cin);
		void set_secret_world(std::ostream& out = std::cout, std::istream& in = std::cin) ;
		inline Account get_new_account() const noexcept { return m_new_user; }
private :
	Account m_new_user;
};

 class SignIn
{
	public :
			SignIn() = default;
			~SignIn() = default;
	public :
			template <JsonType Container>
			bool find_user(Container& list, const std::string& name, std::ostream& out = std::cout)
			{
				for (auto account : list)
				if(account.contains(KEY1))
				{
					toDecode.set_CalcCoeff(account[KEY1]);
						if (account.contains(USERNAME) && toDecode(account[USERNAME]) == name)
						{
							m_user = deserializeFromJson(account);
								return true;
						}
	     		}
			out << "User is undefined !" << std::endl ;
			return false ;
			};
			bool forgot_password(std::ostream& out = std::cout, std::istream& in = std::cin, std::function <bool(const std::string&)> password_criteri = default_criteri)
			{
				out << "Please Enter your secret word > " << std::endl;
				in.clear();
				std::string data;
				in >> data;
				if (m_user.check_secretword(data))
				{
					out << "Done! Now please Enter new password ! " << std::endl;
					in.clear();
					in >> data;
					if (password_criteri(data))
					{
						m_user.change_password(data);
						return true;
					}
					else
					{
						out << "Your password is too easy ! Try again. " << std::endl;
						return false;
					}	
				}
				else
				{
					out << "Wrong Secret Word !" << std::endl;
					return false;
				}
			};
			bool change_password(std::ostream& out = std::cout, std::istream& in = std::cin, std::function <bool(const std::string&)> password_criteri = default_criteri)
			{
				out << "Please enter your password: ";
				in.clear();
				std::string data;
				in >> data;
				if (m_user.check_password(data))
				{
					out << "Plese enter your new password: ";
					in.clear();
					in >> data;
					if (password_criteri(data))
					{
						m_user.change_password(data);
						return true;
					}
					else
						out << "Your Password is too easy! " << std::endl;
				}
				return false;
			};
			template <JsonType Container>
			bool save_changes(Container& list)
			{
				for (auto user_json : list)
				{ 
					if (user_json.contains(KEY1))
					{
						toDecode.set_CalcCoeff(user_json[KEY1]);
							if (user_json.contains(USERNAME) && toDecode(user_json[USERNAME]) == m_user.get_username())
							{
								user_json = makeJson(m_user);
									return true;
							}
					}
				}
				return false ;
			};
			inline bool check_password(const std::string& passw) const noexcept { return m_user.check_password(passw); }
private:
		Account m_user;
};
