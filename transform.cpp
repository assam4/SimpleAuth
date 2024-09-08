#include "transform.hpp"
#include <random>

std::string Code::operator()(const std::string& data) //  Using random generated cooefficient and one static coefficient for coding data , to garanted security
{
	m_inputCoefficient = data.size();
	std::random_device  generator;
	std::uniform_int_distribution<> range(1, m_inputCoefficient);
	m_calculatedCoefficient = m_inputCoefficient % range(generator);
	std::string coded_data;
	for (const auto& letter : data)
		{
			int number = int(letter + m_inputCoefficient + m_calculatedCoefficient);
			char coded_letter = (number > MAX_LET_VAL) ? char(number - MAX_LET_VAL) : char(number);
			coded_data += coded_letter;
		}
	return coded_data;
}  

std::string Decode::operator()(const std::string& data) // decoding data with using coefficients
{
	m_inputCoefficient = data.size();
	std::string decoded_data;
	for (const auto& letter : data)
		{
			int number = int(letter - m_inputCoefficient - m_calculatedCoefficient);
			char decoded_letter = (number < MIN_LET_VAL) ? char(number + MAX_LET_VAL) : char(number);
			decoded_data += decoded_letter;
		}
	return decoded_data;
} 

json makeJson(const Account& object) // function make json type object with all coded data and save their keys to decode later
{
	json user_data;
	user_data[USERNAME] = toCode(object.get_username());   
	user_data[KEY1] = toCode.get_CalcCoeff();
	user_data[PASSWORD] = toCode(object.get_password());
	user_data[KEY2] = toCode.get_CalcCoeff();
	user_data[SECRET_WORD] = toCode(object.get_secretword());
	user_data[KEY3] = toCode.get_CalcCoeff();
	return user_data;
}  

Account deserializeFromJson(const json& data) // function returned type account object uses keys to decode user data
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
	return Account(username, password, secret_word);
} 

