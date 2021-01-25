#pragma once

#include <string>
#include <vector>
#include <unordered_map>

class ValueWrapper
{
public:
	ValueWrapper();
	ValueWrapper(std::string value);

	operator std::string() const;

	template <typename T>
	T as() const
	{
		if (isDefaultValue)
		{
			return (T)0;
		}

		return _as<T>();
	}

	template <>
	std::string as() const
	{
		return value;
	}

private:
	template <typename T>
	T _as() const;

	std::string value;
	bool isDefaultValue = false;
};

template<> int ValueWrapper::_as() const;
template<> long ValueWrapper::_as() const;
template<> long long ValueWrapper::_as() const;
template<> unsigned long ValueWrapper::_as() const;
template<> unsigned long long ValueWrapper::_as() const;
template<> float ValueWrapper::_as() const;
template<> double ValueWrapper::_as() const;
template<> long double ValueWrapper::_as() const;
template<> bool ValueWrapper::_as() const;

class Arguments
{
public:
	Arguments(const std::vector<std::string>& tokens);

	bool has(const std::string& name) const;
	const ValueWrapper& get(const std::string& name) const;

	bool has(unsigned int idx) const;
	const ValueWrapper& get(unsigned int idx) const;
private:
	std::vector<ValueWrapper> unnamedArgs;
	std::unordered_map<std::string, ValueWrapper> namedArgs;
};
