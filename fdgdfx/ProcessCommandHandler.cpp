#include "ProcessCommandHandler.h"
#include "ConsoleManager.h"
#include <iostream>

ProcessCommandHandler::ProcessCommandHandler(ConsoleManager& consoleManager)
	: consoleManager(consoleManager){}

void ProcessCommandHandler::handleCommand(const std::string& command) const {
	if (command == "process -smi") {
		std::cout << "doing something" << std::endl;
	}
	else if(command == "exit") {
		std::cout << "exiting process console..." << std::endl;
		const_cast<ProcessCommandHandler*>(this)->exit = true;
		system("cls"); 
		consoleManager.showMainMenu();

		//exit = true; 
	}
	else {
		std::cout << "Command not recognized." << std::endl;
	}
}

bool ProcessCommandHandler::shouldExit() const {
	return exit; 
}

void ProcessCommandHandler::resetExitFlag() {
	exit = false; 
}