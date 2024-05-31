#include "console_manager.h"

const std::string RED = "\033[1;31m";
const std::string DEFAULT = "\033[0m";

console_manager::console_manager()
{
	initializeMainScreen(); // Initialize the main screen
}

void console_manager::clear()
{
#ifdef _WIN64
	system("cls");
#else
	system("clear");
#endif
}
void console_manager::screenCommand_c(const std::string &command)
{
	if (command == "exit")
	{
		if (currentScreen != "mainScreen")
		{
			currentScreen = "mainScreen"; // Go back to the main screen
			show(currentScreen);
		}
		else
		{
			exit(0); // Exit the program if already in mainScreen
		}
	}
	else if (command.rfind("screen -r ", 0) == 0)
	{
		std::string screenName = command.substr(10);
		// Create a new screen if it doesn't exist
		if (!screenContents.count(screenName))
		{
			screenContents[screenName] = "New screen created: " + screenName;
		}
		currentScreen = screenName; // Set the current screen
		show(screenName);
	}
	else
	{
		std::cout << RED << "Command not recognized." << "\n"
				  << DEFAULT;
	}
}

// for getting the timestamp
std::string console_manager::timeStamp()
{
	std::time_t now = std::time(nullptr);
	char buf[100];

	struct tm t;
#ifdef _WIN32
	localtime_s(&t, &now);
#else
	localtime_r(&now, &t);
#endif

	std::strftime(buf, sizeof(buf), "%m/%d/%Y, %I:%M:%S %p", &t);
	return buf;
}

// display contents of the screen
void console_manager::show(const std::string &screenName)
{
	clear();
	std::cout << "Screen: " << screenName << "\n";
	std::cout << "Content: " << screenContents[screenName] << "\n";
	std::cout << "Timestamp: " << timeStamp() << "\n";
}

/*
std::string command;

while (true) {
std::cout << "Enter Command: ";
std::getline(std::cin, command); //get the whole input line

if (command == "exit") {
break; // Exit the loop and end the program
}
else if (command == "clear") {
clear();
}
}
*/