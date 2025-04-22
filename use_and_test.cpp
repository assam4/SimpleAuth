#include "application.hpp"

bool	testing_codedecode(void)
{
	std::string	name("Rafael Morena");
	auto		coded_data = toCode(name);
	auto		coeff_2 = toCode.get_CalcCoeff();
	toDecode.set_CalcCoeff(coeff_2);
	auto		decoded_data = toDecode(coded_data);
	std::cout << "Original Data:[ "<< name << "]\n" 
		<< "Coded Data:[" << coded_data <<  "]\n"
		<< "Decoded Data:[" << decoded_data  << "]" << std::endl;
	if (name == decoded_data)
		return (true);
	else
		return (false);
}

bool	testing_formatetransforms(void)
{
	Account		test("Maria", "mypasswordisatoeasy", "Donalds");
	auto		format_json = makeJson(test);
	std::cout << "Formated data:\n"
		<< " username [ " << format_json[USERNAME] << " ]\n"
		<< " password [ " << format_json[PASSWORD] << " ]\n"
		<< " secretword [ " << format_json[SECRET_WORD] << " ]\n"
		<< std::endl;
	Account		result = deserializeFromJson(format_json);
	std::cout << "Deformated data : " << " username " << result.get_username()
		<< " password " << result.get_password() 
		<< " secretword " << result.get_secretword() 
		<< std::endl;
	if (test.get_username() != result.get_username())
		return (false);
	if (test.get_password() != result.get_password()) 
		return (false);
	if (test.get_secretword() != result.get_secretword()) 
		return (false);
	return (true);								
}

bool	testing_passwordcriteri(std::function<bool(const std::string&)> password_criteri = default_criteri)
{
	std::string wrong = "badpassword";
	bool	iscorresponds = password_criteri(wrong);
	std::cout << std::boolalpha;
	std::cout << "the password " << wrong << " is a " << iscorresponds << std::endl;
	std::string correct = "GoodPassword7";
	bool	iscorresponds2 = password_criteri(correct);
	std::cout << "the password " << correct << " is a " << iscorresponds2 << std::endl;
	std::cout << std::noboolalpha;
	return ((!iscorresponds && iscorresponds2) ? true : false);
}

// using vector for contains User accounts
std::vector<json>	list;

template <JsonType container>
bool	testing_registration(container& list)
{
	Registration	reg;
	reg.set_username(list);
	reg.set_password();
	while (!reg.repeat_password())
	{ }
	reg.set_secret_word();
	auto	newuser = reg.get_new_account();
	auto	json = makeJson(newuser);
	list.push_back(json);
	return (true);
};

template <JsonType container>
bool	testing_login(container& list)
{
	SignIn		login;
	int		count{START_VAL};
	std::string	data;

	std::cout << COM_COLOR << "Enter Username: " << DEF_COLOR;
	std::cin.clear();
	std::cin >> data;
	if (login.find_user(list, data))
	{
		do
		{
			std::cout << COM_COLOR << "Enter your Password: " << DEF_COLOR;
			std::cin.clear();
			std::cin >> data;
			if (login.check_password(data))
			{
				std::cout << OK_COLOR << "Good. You signed!"
					<< DEF_COLOR << std::endl;
				break ;
			}
			else
			{
				if (++count == 3) break;
				std::cout << WARNING_COLOR << "Wrong! Try again !"
					<< DEF_COLOR << std::endl;
				continue ;
			}
		} while (true);
	}
	else
		return (false);
	std::cout << COM_COLOR << "MENU\n"
			<< "'1' - to change secret word\n"
			<< "'2' - to change password "
			<< std::endl;
	int choice{START_VAL};
	std::cin.clear();
	std::cin >> choice;
	switch (choice)
	{
		case 1:
			if (login.forgot_password())
				count = START_VAL;
			break ;
		case 2:
			if (login.change_password())
				count = START_VAL;
			break ; 
	}
	login.save_changes(list);
	return (count == START_VAL);
}

int	main(void)
{
	bool test1 = testing_codedecode();
	bool test2 = testing_formatetransforms();
	bool test3 = testing_passwordcriteri();
	bool test4 = testing_registration(list);
	bool test5 = testing_login(list);
	if (test1)
		std::cout << "Code-Decode test:  OK!" << std::endl;
	if (test2)
		std::cout << "Formating test:    OK!" << std::endl;
	if (test3)
		std::cout << "PwdCriteri test:   OK!" << std::endl;
	if (test4)
		std::cout << "Registration test: OK!" << std::endl;
	if (test5)
		std::cout << "Login test:        OK!" << std::endl;
	return (EXIT_SUCCESS);
}
