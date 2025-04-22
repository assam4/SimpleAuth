#pragma once

# include <nlohmann/json.hpp>
# include <random>
# include <functional>
# include "account.hpp"

# define PURE_VIRTUAL 0
# define START_VAL 0


inline constexpr const char*	USERNAME = "username: ";
inline constexpr const char*	PASSWORD = "password: ";
inline constexpr const char*	SECRET_WORD = "secret_word: ";
inline constexpr const char*	KEY1 = "nme_coeff";
inline constexpr const char*	KEY2 = "pwd_coeff";
inline constexpr const char*	KEY3 = "swd_coeff";
static constexpr size_t		PASSWD_MIN_LEN{8};
static constexpr char		MIN_PRINT_CHAR{32};
static constexpr char		MAX_PRINT_CHAR{127};

class Code_Decode
{
public:
	Code_Decode()
	: m_inputCoefficient(START_VAL)
	, m_calculatedCoefficient(START_VAL)
	{ }
	virtual ~Code_Decode() = default;
public:
	virtual std::string operator()(const std::string&) = PURE_VIRTUAL;
protected:
	size_t m_inputCoefficient;
	int m_calculatedCoefficient;
};

class Code: public Code_Decode
{
public:
	Code()
	: Code_Decode()
	{ }
	~Code() override = default ;
public:
	std::string	operator()(const std::string& data) override;
	inline int	get_CalcCoeff() const noexcept
	{return (m_calculatedCoefficient);}
};

class Decode: public Code_Decode
{
public:
	Decode()
	: Code_Decode()
	{ }
	~Decode() override = default;
public:
	std::string	operator()(const std::string& data ) override;
	inline void set_CalcCoeff(int coeff) noexcept
	{m_calculatedCoefficient = coeff;}
};

static Code toCode;
static Decode toDecode;

using json = nlohmann::json;

json	makeJson(const Account& );
Account	deserializeFromJson(const json&);
extern std::function<bool(const std::string&)> default_criteri;
