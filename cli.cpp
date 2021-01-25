#include "cli.h"

#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>

int quit()
{
	exit(0);
	return 0;
}

CLI::CLI(std::unordered_map<std::string, CommandInfo> commands) : commands(commands)
{
	this->commands.insert_or_assign("help", CommandInfo{ "Displays help for the given command", [this](const Arguments& args) -> int { return help(args); } });
	this->commands.insert_or_assign("exit", CommandInfo{ "Exits the program", [](const Arguments&) { return quit(); } });
	this->commands.insert_or_assign("quit", CommandInfo{ "Exits the program", [](const Arguments&) { return quit(); } });
}

int CLI::run(int argc, char* argv[]) const
{
	if (argc > 1)
	{
		const std::vector<std::string> tokens(argv + 1, argv + argc);
		const auto command = Command(tokens);
		return executeCommand(command);
	}

	runShell();

	return 0;
}

auto& getInputLine(std::string& line)
{
	std::cout << "wpe > ";
	return std::getline(std::cin, line);
}

void CLI::runShell() const
{
	std::string line;

	while (getInputLine(line))
	{
		if (!line.empty())
		{
			const auto command = Command(line);
			executeCommand(command);
		}
	}
}

int CLI::executeCommand(const Command& command) const
{
	const auto it = commands.find(command.name);
	if (it == commands.end())
	{
		printUsage(command.name);
		return -1;
	}

	return it->second.execute(command.args);
}

void CLI::printUsage(const std::string& name) const
{
	std::cout << "Command \"" << name << "\" not found." << std::endl;
	printUsage();
}

void CLI::printUsage() const
{
	std::cout << "Available commands:" << std::endl;

	for (const auto& command : commands)
	{
		std::cout << command.first << std::endl;
	}

	std::cout << "For more information on a command type \"help <command name>\"" << std::endl;
}

int CLI::help(const Arguments& args)
{
	if (args.has(0))
	{
		const auto& commandName = args.get(0);
		const auto it = commands.find(commandName);
		if (it == commands.end())
		{
			printUsage(commandName);
			return 0;
		}

		std::cout << it->second.description << std::endl;
	}
	else
	{
		printUsage();
	}

	return 0;
}
