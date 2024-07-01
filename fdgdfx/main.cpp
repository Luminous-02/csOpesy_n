#include <iostream>
#include "MainMenuConsole.h"
#include "MainMenuCommandHandler.h"
#include "ConsoleManager.h"

int main() {

	ConsoleManager consoleManager;

	//MainMenuCommandHandler mainMenuCommandHandler(consoleManager);
	//MainMenuConsole mainMenuConsole(&mainMenuCommandHandler);
	//mainMenuConsole.displayPrompt();

	consoleManager.showMainMenu(); 
	return 0;
}