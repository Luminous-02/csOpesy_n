#pragma once

#include "CommandHandler.h"
#include "ConsoleManager.h"
#include <string>
#include <memory>
#include <map>

class MainMenuCommandHandler : public CommandHandler
{
public:
	MainMenuCommandHandler(ConsoleManager& consoleManager);
	void handleCommand(const std::string& command) const override;

private:
	std::map<std::string, std::unique_ptr<Process>> processes;

	ConsoleManager& consoleManager;
	mutable bool initialized;
};

