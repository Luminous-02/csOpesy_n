#pragma once

#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <iostream>
#include "Process.h"
#include "static.h"
#include "CommandHandler.h"
#include <map>

class Console {
private:
	std::string consoleName;

public:
	Console(const std::string& name)
		: consoleName(name) {}

	//this will be overidden by thhe derived class
	virtual ~Console() = default;

	virtual void displayHeader() const {
		return printHeader();
	}

	virtual std::string getCommand() {
		std::string command;
		std::cout << "Enter command: ";
		std::getline(std::cin, command);
		return command;
	}
};

class MainMenuConsole : public Console {
private:
	CommandHandler commandHandler;
	//std::map<std::string, ProcessConsole> processConsoles;

public:
	MainMenuConsole() : Console("Main Menu") {}

	/*void addProcessConsole(const std::string& name, Process process) {
		processConsoles[name] = ProcessConsole(name, process);
	}*/

	void run() {
		displayHeader();

		while (true) {
			std::string command = getCommand();
			commandHandler.handleCommand(command);

			if (command == "exit") {
				std::cout << "Exiting...\n";
				break;
			}
			/*

			if (command.find("screen -r") == 0 || command.find("screen -s") == 0) {
				std::string screenName = command.substr(10);

				if (processConsoles.find(screenName) != processConsoles.end()){
					processConsoles[screenName].run();
				}
				else {
					std::cout << "Process not found: " << screenName << "\n";
				}
			}*/
		}
	}
};

/*
class ProcessConsole : public Console {
private:
	Process process;

public:
	ProcessConsole(const std::string& name, Process process)
		: Console(name), process(process) {}

	void displayHeader() const override {
		std::cout << "Process Name: " << consoleName << "\n";
		std::cout << "Current Line: " << process.getCurrentLine() << " / " << process.getTotalLines() << "\n";
		std::cout << "TImestamp: " << process.getTimeStamp() << "\n";
	}

	void run() {
		while (true) {
			displayHeader();
			std::string command = getCommand();

			if (command == "exit") {
				std::cout << "Returning to main menu...\n";
				break;
			}
		}
	}
};*/