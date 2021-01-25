#include "command.h"

std::vector<std::string> tokenize(const std::string& str)
{
	bool isEscaped = false;
	bool isQuoted = false;

	std::vector<std::string> tokens;
	std::string currentToken;
	for (char c : str)
	{
		if (c == ' ')
		{
			if (!isQuoted)
			{
				if (!currentToken.empty())
				{
					tokens.push_back(currentToken);
				}
				currentToken.clear();
				continue;
			}
		}
		else if (c == '"')
		{
			if (!isEscaped)
			{
				isQuoted = !isQuoted;
				continue;
			}
			currentToken.pop_back();
		}
		else if (c == '\\')
		{
			isEscaped = true;
			currentToken += c;
			continue;
		}

		currentToken += c;
		isEscaped = false;
	}

	tokens.push_back(currentToken);

	return (std::move(tokens));
}

Command::Command(const std::string& line)
	: Command(tokenize(line))
{
}

Command::Command(const std::vector<std::string>& tokens) : name(tokens.front()), args(std::vector(tokens.begin() + 1, tokens.end()))
{
}
