#include "ProcessCommandHandler.h"
#include "ConsoleManager.h"
#include <iostream>

ProcessCommandHandler::ProcessCommandHandler(ConsoleManager& consoleManager)
	: consoleManager(consoleManager), exit(false) {}

void ProcessCommandHandler::handleCommand(const std::string& command) {
	if (command == "process -smi") {

		auto& processes = consoleManager.getSchedProcesses(); //get the list
		const std::string& currentProcessName = consoleManager.getCurrentProcessName(); //search by name

		auto it = processes.find(currentProcessName); 

		if (it != processes.end()) {
			Process* process = it->second.get();

			std::cout << "\nProcess: " << process->getName() << std::endl;
			std::cout << "ID: " << process->getID() << std::endl;

			std::cout << "\n"; 

			if (process->getStatus() == Process::ProcessState::FINISHED) {
				std::cout << "Finished!" << std::endl;

				std::cout << "\n";
			}
			else {

				std::cout << "Current intstruction line: " << process->getCurrentLine() << std::endl;
				std::cout << "Lines of code: " << process->getTotalLines() << std::endl;

				std::cout << "\n";
			}
		}
		else {
			std::cout << "Process not found!" << std::endl; 
		}

		exit = false;
	}
	else if(command == "exit") {
		std::cout << "exiting process console..." << std::endl;
		const_cast<ProcessCommandHandler*>(this)->exit = true;
		system("cls"); 
		consoleManager.showMainMenu();

		exit = true; 
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