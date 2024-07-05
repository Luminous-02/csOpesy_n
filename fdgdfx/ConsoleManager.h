#pragma once


#include "Console.h"
#include "Process.h"

#include <iostream>
#include <map>
#include <memory>
#include <unordered_map>

#include "CommandHandler.h"
#include "ProcessCommandHandler.h"
#include "MainMenuCommandHandler.h"
#include "ConfigurationManager.h"
#include "Scheduler.h"


class MainMenuCommandHandler;


class ConsoleManager
{
public:
	ConsoleManager(ConfigurationManager& configurationManager);
	
	ConfigurationManager& getConfigurationManager();

	void setConsole(Console* console);

	void displayPrompt() const; //mainmenu
	std::string getCommand() const;

	void addProcess(const std::string& processName, std::unique_ptr<Process> process);
	void displayProcessScreen(const std::string& processName);

	void createNewProcess(const std::string& processName); 

	void showMainMenu(); 

	bool isInitialized() const; //check if system has been initialized
	void setInitialized(bool initialized); 

	std::unordered_map<std::string, std::unique_ptr<Process>>& getSchedProcesses(); 

	std::string getCurrentProcessName() const; 

	void listProcesses() const;

private:
	Console* console;

	CommandHandler* currentCommandHandler; 
	std::unique_ptr<MainMenuCommandHandler> mainMenuCommandHandler;
    std::unique_ptr<ProcessCommandHandler> processCommandHandler;

	bool initialized;

	ConfigurationManager configManager;

	std::unordered_map<std::string, std::unique_ptr<Process>> processes;

	std::string currentProcessName;
};

