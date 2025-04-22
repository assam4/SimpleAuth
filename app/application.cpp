#include "application.hpp"

bool	Registration::repeat_password(std::ostream& out, std::istream& in)
{
	std::string repeat;
	out << COM_COLOR << "Please repeat password: " << DEF_COLOR;
	in.clear();
	in >> repeat;
	if (repeat == m_new_user.get_password())
		return (true);
	else
		return (out << ERROR_COLOR << "Passwords don't match!." << DEF_COLOR << std::endl
			, false);
}
void	Registration::set_secret_word(std::ostream& out, std::istream& in)
{
	std::string data;
	out << COM_COLOR << "Choose your secret word: " << DEF_COLOR;
	in.clear();
	in >> data;
	if (data.empty()) data = DEFAULT_WORD;
	m_new_user.change_word(data);
}
