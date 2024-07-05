#include <iostream>
#include "MainMenuConsole.h"
#include "MainMenuCommandHandler.h"
#include "ConsoleManager.h"
#include "ConfigurationManager.h"

int main() {


	ConfigurationManager configManager; 

	ConsoleManager consoleManager(configManager);

	//MainMenuCommandHandler mainMenuCommandHandler(consoleManager);
	//MainMenuConsole mainMenuConsole(&mainMenuCommandHandler);
	//mainMenuConsole.displayPrompt();

	consoleManager.showMainMenu(); 
	return 0;
}