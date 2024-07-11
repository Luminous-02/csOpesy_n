#include "MainMenuCommandHandler.h"
#include "ConsoleManager.h"
#include "Scheduler.h"
#include "marquee.h"
#include "Statics.h"
#include <iostream>
#include <fstream> 
#include <sstream>

class ConsoleManager; 

MainMenuCommandHandler::MainMenuCommandHandler(ConsoleManager& consoleManager)
	: consoleManager(consoleManager),
	  configManager(consoleManager.getConfigurationManager()){}

MainMenuCommandHandler::~MainMenuCommandHandler() {
	stopScheduler();
}

void MainMenuCommandHandler::handleCommand(const std::string& command) {

	//static std::unique_ptr<Scheduler> scheduler;

	//check the valid commands for the MainMenu
	if (!consoleManager.isInitialized()) {
		if (command == "initialize") {

			consoleManager.getConfigurationManager().loadConfig("config.txt");
			//consoleManager.getConfigurationManager().printConfig();

			std::cout << "Initialization complete. \n";
			consoleManager.setInitialized(true);
			//consoleManager.getConfigurationManager().getNumCpu(); 

			startScheduler();
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

			auto& processes = consoleManager.getSchedProcesses();
			auto it = processes.find(processName);
			if (it != processes.end()) {
				scheduler->executeProcess(it->second.get());
			}
			
			MainMenuCommandHandler* nonConstThis = const_cast<MainMenuCommandHandler*>(this);

			consoleManager.displayProcessScreen(processName);

			
			nonConstThis->exitFlag = true;
		}
		else if (command.substr(0, 9) == "screen -r") {
			std::string processName = command.substr(10);
			system("cls");

			consoleManager.displayProcessScreen(processName);

			exitFlag = true;
		}
		else if (command == "screen -ls") {
			consoleManager.listProcesses();
		}
		else if (command == "marquee") {
			displayMarquee();
			system("cls");
			printHeader();
		}
		else if (command == "scheduler-test") {
			std::cout << "doing something\n";
		}
		else if (command == "report-util") {
			consoleManager.reportlistProcesses();
		}
		else if (command == "exit") {
			exitFlag = true;
			stopScheduler();
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

void MainMenuCommandHandler::startScheduler() {
	scheduler = std::make_unique<Scheduler>(consoleManager.getConfigurationManager().getNumCpu(),
		consoleManager.getConfigurationManager().getScheduler(),
		consoleManager.getConfigurationManager().getQuantumCycles(),
		consoleManager.getConfigurationManager().isPreemptive(),
		consoleManager.getSchedProcesses());

	schedulerThread = std::thread([this]() {
		try {
			scheduler->start();
		}
		catch (const std::exception& e) {
			std::cerr << "Scheduler thread exception: " << e.what() << std::endl;
		}
		catch (...) {
			std::cerr << "Scheduler thread unknown exception" << std::endl;
		}
		});
}

void MainMenuCommandHandler::stopScheduler() {
	if (scheduler) {
		scheduler->stop();
		if (schedulerThread.joinable()) {
			schedulerThread.join();
		}

		scheduler.reset();
	}
}