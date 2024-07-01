#include "MainMenuCommandHandler.h"
#include "ConsoleManager.h"
#include "Statics.h"
#include <iostream>
#include <fstream> 
#include <sstream>

class ConsoleManager; 

MainMenuCommandHandler::MainMenuCommandHandler(ConsoleManager& consoleManager)
	: consoleManager(consoleManager), configManager(configManager){}

void MainMenuCommandHandler::handleCommand(const std::string& command) const {

	//check the valid commands for the MainMenu
	if (!consoleManager.isInitialized()) {
		if (command == "initialize") {

			consoleManager.getConfigurationManager().loadConfig("config.txt");
			consoleManager.getConfigurationManager().printConfig();

			std::cout << "Initialization complete. \n";
			consoleManager.setInitialized(true);
		}
		else {
			std::cout << "Please initialize first using 'initialize' command. \n";
		}
	}
	else {
		if (command.substr(0, 9) == "screen -s") {
			std::string processName = command.substr(10); //extract the processName
			system("cls"); 
			consoleManager.createNewProcess(processName);
			consoleManager.displayProcessScreen(processName);
			const_cast<MainMenuCommandHandler*>(this)->exitFlag = true;
		}
		else if (command == "screen") {
			std::cout << "doing something\n";
		}
		else if (command == "marquee") {
			std::cout << "doing something\n";
		}
		else if (command == "scheduler-test") {
			std::cout << "doing something\n";
		}
		else if (command == "report-util") {
			std::cout << "doing something\n";
		}
		else if (command == "exit") {
			const_cast<MainMenuCommandHandler*>(this)->exitFlag = true;
			//exitFlag = true; 
		}
		else if (command == "clear") {
			system("cls");
			printHeader();
		}
		else {
			std::cout << "Unknown Command: " << command << std::endl;
		}
	}
}

bool MainMenuCommandHandler::shouldExit() const {
	return exitFlag; 
}

void MainMenuCommandHandler::resetExitFlag() {
	exitFlag = false; 
}