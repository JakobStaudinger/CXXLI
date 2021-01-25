#include "arguments.h"

ValueWrapper defaultValue;

Arguments::Arguments(const std::vector<std::string>& tokens)
{
	std::string prevToken;
	bool wasPrevOption = false;

	for (const std::string& token : tokens)
	{
		bool isOption = token.starts_with("--");

		if (isOption)
		{
			namedArgs.insert({ token, ValueWrapper("") });
		}
		else
		{
			if (wasPrevOption)
			{
				namedArgs.at(prevToken) = token;
			}
			else
			{
				unnamedArgs.push_back(token);
			}
		}

		prevToken = token;
		wasPrevOption = isOption;
	}
}

bool Arguments::has(const std::string& name) const
{
	return namedArgs.contains(name);
}

const ValueWrapper& Arguments::get(const std::string& name) const
{
	auto it = namedArgs.find(name);
	if (it != namedArgs.end())
	{
		return it->second;
	}
	return defaultValue;
}

bool Arguments::has(unsigned int idx) const
{
	return idx < unnamedArgs.size();
}

const ValueWrapper& Arguments::get(unsigned int idx) const
{
	return has(idx) ? unnamedArgs[idx] : defaultValue;
}

ValueWrapper::ValueWrapper() : isDefaultValue(true)
{
}

ValueWrapper::ValueWrapper(std::string value) : value(value)
{
}

ValueWrapper::operator std::string() const
{
	return value;
}

template<> int ValueWrapper::_as() const
{
	return std::stoi(value, nullptr, 0);
}

template<> long ValueWrapper::_as() const
{
	return std::stol(value, nullptr, 0);
}

template<> long long ValueWrapper::_as() const
{
	return std::stoll(value, nullptr, 0);
}

template<> unsigned long ValueWrapper::_as() const
{
	return std::stoul(value, nullptr, 0);
}

template<> unsigned long long ValueWrapper::_as() const
{
	return std::stoull(value, nullptr, 0);
}

template<> float ValueWrapper::_as() const
{
	return std::stof(value);
}

template<> double ValueWrapper::_as() const
{
	return std::stod(value);
}

template<> long double ValueWrapper::_as() const
{
	return std::stold(value);
}

template<> bool ValueWrapper::_as() const
{
	if (value == "false" || value == "FALSE" || value == "0")
	{
		return false;
	}

	return true;
}
