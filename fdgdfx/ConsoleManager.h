#pragma once


#include "Console.h"
#include "Process.h"

#include <iostream>
#include <map>
#include <memory>

#include "CommandHandler.h"
#include "ProcessCommandHandler.h"
#include "MainMenuCommandHandler.h"
#include "ConfigurationManager.h"

class MainMenuCommandHandler;


class ConsoleManager
{
public:
	ConsoleManager();

	void setConsole(Console* console);

	void displayPrompt() const; //mainmenu
	std::string getCommand() const;

	void addProcess(const std::string& processName, std::unique_ptr<Process> process);
	void displayProcessScreen(const std::string& processName);

	void createNewProcess(const std::string& processName); 

	void showMainMenu(); 

	bool isInitialized() const; //check if system has been initialized
	void setInitialized(bool initialized); 

	ConfigurationManager& getConfigurationManager();

private:
	Console* console;
	
	std::map<std::string, std::unique_ptr<Process>> processes;

	CommandHandler* currentCommandHandler; 
	std::unique_ptr<MainMenuCommandHandler> mainMenuCommandHandler;
    std::unique_ptr<ProcessCommandHandler> processCommandHandler;

	bool initialized;

	ConfigurationManager configManager;
};

