#include "MainMenuCommandHandler.h"
#include "ConsoleManager.h"
#include "Scheduler.h"

#include "Statics.h"
#include <iostream>
#include <fstream> 
#include <sstream>

class ConsoleManager; 

MainMenuCommandHandler::MainMenuCommandHandler(ConsoleManager& consoleManager)
	: consoleManager(consoleManager),
	  configManager(consoleManager.getConfigurationManager()){}



void MainMenuCommandHandler::handleCommand(const std::string& command) const {

	//static std::unique_ptr<Scheduler> scheduler;

	//check the valid commands for the MainMenu
	if (!consoleManager.isInitialized()) {
		if (command == "initialize") {

			consoleManager.getConfigurationManager().loadConfig("config.txt");
			consoleManager.getConfigurationManager().printConfig();

			std::cout << "Initialization complete. \n";
			consoleManager.setInitialized(true);
			//consoleManager.getConfigurationManager().getNumCpu(); 
			
			scheduler = std::make_unique<Scheduler>(consoleManager.getConfigurationManager().getNumCpu(),
				consoleManager.getConfigurationManager().getScheduler(),
				consoleManager.getConfigurationManager().getQuantumCycles(),
				consoleManager.getConfigurationManager().isPreemptive(),
				consoleManager.getSchedProcesses());

			scheduler->start();
			
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
			
			MainMenuCommandHandler* nonConstThis = const_cast<MainMenuCommandHandler*>(this);

			consoleManager.displayProcessScreen(processName);

			nonConstThis->exitFlag = true;
		}
		else if (command.substr(0, 9) == "screen -r") {
			std::string processName = command.substr(10);
			system("cls");

			consoleManager.displayProcessScreen(processName);

			MainMenuCommandHandler* nonConstThis = const_cast<MainMenuCommandHandler*>(this);
			nonConstThis->exitFlag = true;
		}
		else if (command == "screen -ls") {
			consoleManager.listProcesses();
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
			//scheduler->stop();
			const_cast<MainMenuCommandHandler*>(this)->exitFlag = true;
			
			if (scheduler) {
				scheduler->stop();
			}

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
