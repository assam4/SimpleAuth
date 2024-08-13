#pragma once
#include <nlohmann/json.hpp>
#include "account.hpp"

//  declare to use keys
extern const std::string USERNAME;
extern const std::string PASSWORD;
extern const std::string SECRET_WORD;
extern const std::string KEY1;
extern const std::string KEY2;
extern const std::string KEY3;

class Code_Decode
{
public : 
		Code_Decode()	
			:	m_inputCoefficient(NULL)
			,	m_calculatedCoefficient(NULL)
		{ }
		virtual ~Code_Decode() = default;
public :
		virtual std::string operator()(const std::string&) = 0;
protected :
			size_t m_inputCoefficient;
			int m_calculatedCoefficient;
};

class Code : public Code_Decode
{
public : 
		Code() : Code_Decode() {}
		~Code() override = default ;
public :
		std::string operator()(const std::string& data) override;
		inline int get_CalcCoeff() const noexcept { return m_calculatedCoefficient; }
};

class Decode : public Code_Decode
{
public :
		Decode() : Code_Decode() {}
		~Decode() override = default;
public :
		std::string operator()(const std::string& data ) override;
		inline void set_CalcCoeff(int coeff) { m_calculatedCoefficient = coeff; }
};

// global objects for code_decoding data
static Code toCode;
static Decode toDecode;

// formating part
using json = nlohmann::json;

json makeJson(const Account& );
Account deserializeFromJson(const json&);

// password criteri |  using lyamba

inline auto default_criteri = [&](const std::string& sample) ->bool const 
	{
		if (PASSWORD_MIN_SIZE > sample.size()) return false;
		else
		{
			bool isUpper = false , isLower = false , isDigit = false;
			for (const auto& letter : sample)
			{
				if (letter < MIN_LET_VAL || letter > MAX_LET_VAL)
					return false;
				else if (std::isupper(letter))
					isUpper = true;
				else if (std::islower(letter))
					isLower = true;
				else if (std::isdigit(letter))
					isDigit = true;
			}
			return (isUpper && isLower && isDigit);
		}
	};
