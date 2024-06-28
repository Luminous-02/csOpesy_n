#include "MainMenuConsole.h"
//#include "CommandHandler.h"

#include "Statics.h"
#include <iostream>

MainMenuConsole::MainMenuConsole(CommandHandler* commandHandler)
	: commandHandler(commandHandler) {}

void MainMenuConsole::displayPrompt() const {
	printHeader();

	while (true) {
		std::cout << "Enter Command: ";
		std::string command = getCommand();

		commandHandler->handleCommand(command);

		if (command == "exit") {
			break;
		}
	}
}

//get the commands 
std::string MainMenuConsole::getCommand() const {
	std::string command;
	std::getline(std::cin, command);
	return command;
}