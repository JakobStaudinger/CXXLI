#pragma once

#include <unordered_map>
#include <functional>

#include "arguments.h"
#include "command.h"

struct CommandInfo
{
	std::string description;
	std::function<int(const Arguments& args)> execute;
};

class CLI
{
public:
	CLI(std::unordered_map<std::string, CommandInfo>);
	int run(int argc, char* argv[]) const;

private:
	void runShell() const;
	void printUsage(const std::string&) const;
	void printUsage() const;
	int executeCommand(const Command& command) const;
	int help(const Arguments& args);

private:

	std::unordered_map<std::string, CommandInfo> commands;
};
