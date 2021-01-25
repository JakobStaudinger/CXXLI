#pragma once

#include <string>
#include <vector>

#include "arguments.h"

struct Command
{
	Command(const std::string& line);
	Command(const std::vector<std::string>& tokens);

	std::string name;
	Arguments args;
};

