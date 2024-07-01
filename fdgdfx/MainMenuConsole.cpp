#include "MainMenuCommandHandler.h"
#include "MainMenuConsole.h"
#include "CommandHandler.h"


#include "Statics.h"
#include <iostream>

MainMenuConsole::MainMenuConsole(MainMenuCommandHandler* handler)
	: handler(handler) {}

void MainMenuConsole::displayPrompt() const {
	printHeader();

	while (true) {
		std::cout << "Enter Command: ";
		std::string command = getCommand();

		handler->handleCommand(command);

		if (handler->shouldExit()) {
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