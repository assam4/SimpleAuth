#include "transform.hpp"

//  Using random generated cooefficient and one static coefficient for coding data, to garanted security
std::string	Code::operator()(const std::string& data)
{
	std::random_device		generator;
	std::uniform_int_distribution<>	range(1, m_inputCoefficient);
	std::string 			coded_data;
	int				number{START_VAL};
	char				coded_letter{START_VAL};

	m_inputCoefficient = data.size();
	m_calculatedCoefficient = m_inputCoefficient % range(generator);
	for (const auto& letter: data)
	{
		number = (int)(letter + m_inputCoefficient + m_calculatedCoefficient);
		coded_letter = (number > MAX_PRINT_CHAR) ? (char)(number - MAX_PRINT_CHAR) : (char)(number);
		coded_data += coded_letter;
	}
	return (coded_data);
}  

std::string	Decode::operator()(const std::string& data)
{
	std::string 	decoded_data;
	int		number{START_VAL};
	char		decoded_letter{START_VAL};

	m_inputCoefficient = data.size();
	for (const auto& letter: data)
	{
		number = (int)(letter - m_inputCoefficient - m_calculatedCoefficient);
		decoded_letter = (number < MIN_PRINT_CHAR) ? (char)(number + MAX_PRINT_CHAR) : (char)(number);
		decoded_data += decoded_letter;
	}
	return (decoded_data);
} 

json	makeJson(const Account& object)
{
	json user_data;

	user_data[USERNAME] = toCode(object.get_username());   
	user_data[KEY1] = toCode.get_CalcCoeff();
	user_data[PASSWORD] = toCode(object.get_password());
	user_data[KEY2] = toCode.get_CalcCoeff();
	user_data[SECRET_WORD] = toCode(object.get_secretword());
	user_data[KEY3] = toCode.get_CalcCoeff();
	return (user_data);
}  

Account	deserializeFromJson(const json& data)
{
	auto coeff = data[KEY1].get<int>();
	toDecode.set_CalcCoeff(coeff);
	auto username = toDecode(data[USERNAME]);
	coeff = data[KEY2].get<int>();
	toDecode.set_CalcCoeff(coeff);
	auto password = toDecode(data[PASSWORD]);
	coeff = data[KEY3].get<int>();
	toDecode.set_CalcCoeff(coeff);
	auto secret_word = toDecode(data[SECRET_WORD]);
	return (Account(username, password, secret_word));
}

std::function<bool(const std::string&)> default_criteri = [] (const std::string& sample) -> bool
{
	if (PASSWD_MIN_LEN > sample.size())
		return (false);
	else
	{
		bool is_upper = false, is_lower = false, is_digit = false;
		for (const auto& letter: sample)
			if (letter < MIN_PRINT_CHAR || letter > MAX_PRINT_CHAR)
				return false;
			else if (std::isupper(letter))
				is_upper = true;
			else if (std::islower(letter))
				is_lower = true;
			else if (std::isdigit(letter))
				is_digit = true;
	return (is_upper && is_lower && is_digit);
	}
};
