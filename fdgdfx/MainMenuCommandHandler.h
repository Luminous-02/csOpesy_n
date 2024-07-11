#pragma once

#include "CommandHandler.h"
#include "ConsoleManager.h"
#include "ConfigurationManager.h"
#include "Scheduler.h"
#include <thread>

class ConsoleManager;
class Process;

class MainMenuCommandHandler : public CommandHandler
{
public:
	MainMenuCommandHandler(ConsoleManager& consoleManager);
	~MainMenuCommandHandler();
	void handleCommand(const std::string& command) override;
	bool shouldExit() const override; 
	void resetExitFlag() override; 

private:
	ConsoleManager& consoleManager;
	std::map<std::string, std::unique_ptr<Process>> processes;

	mutable bool exitFlag = false; 
	mutable std::unique_ptr<Scheduler> scheduler;
	ConfigurationManager& configManager;

	mutable std::thread schedulerThread;

	void startScheduler();
	void stopScheduler();
};

