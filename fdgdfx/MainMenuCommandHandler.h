#pragma once

#include "CommandHandler.h"
#include "ConsoleManager.h"
#include "ConfigurationManager.h"

class ConsoleManager;
class Process;

class MainMenuCommandHandler : public CommandHandler
{
public:
	MainMenuCommandHandler(ConsoleManager& consoleManager);
	void handleCommand(const std::string& command) const override;
	bool shouldExit() const override; 

	void resetExitFlag() override; 

private:
	ConsoleManager& consoleManager;
	std::map<std::string, std::unique_ptr<Process>> processes;

	mutable bool exitFlag = false; 

	ConfigurationManager& configManager;
};

