#include "MainMenuCommandHandler.h"
#include "ConsoleManager.h"
#include "Statics.h"
#include <iostream>
#include <fstream> 
#include <sstream>

class ConsoleManager; 

MainMenuCommandHandler::MainMenuCommandHandler(ConsoleManager& consoleManager)
	: consoleManager(consoleManager){}

void MainMenuCommandHandler::handleCommand(const std::string& command) const {

	//check the valid commands for the MainMenu
	if (!consoleManager.isInitialized()) {
		if (command == "initialize") {
			//read config.txt
			std::ifstream configFile("config.txt");

			if (configFile.is_open()) {
				std::string line;

				while (std::getline(configFile, line)) {
					std::istringstream iss(line);
					std::string name;
					int id, totalLines;

					if (iss >> name >> id >> totalLines) {
						std::unique_ptr<Process> process = std::make_unique<Process>(name, id, totalLines);
						consoleManager.addProcess(name, std::move(process));
					}
				}

				std::cout << "Initialization complete. \n";
				consoleManager.setInitialized(true);

			}
			else {
				std::cout << "Unable to open config.txt";
			}
		}
		else {
			std::cout << "Please initialize first using 'initialize' command. \n";
		}
	}
	else {
		if (command.substr(0, 9) == "screen -s") {
			std::string processName = command.substr(10); //extract the processName
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