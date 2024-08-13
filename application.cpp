#include "application.hpp"


	bool Registration::repeat_password(std::ostream& out, std::istream& in)
		{
			std::string repeat;
			out << "Please repeat password: ";
			in.clear();
		    in >> repeat;
			if (repeat == m_new_user.get_password())
					return true;
			else
				{
					out << "Wrong !" << std::endl;
					return false;
				}
		}

	void Registration::set_secret_world(std::ostream& out, std::istream& in)
		{
			std::string data;
			out << "Now Choice your secret word: ";
			in.clear();
			in >> data;
			if (data.empty()) data = "default";
			m_new_user.change_secretword(data);
		}
