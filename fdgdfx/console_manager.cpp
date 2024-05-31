///manage the screens
#include "console_manager.h"

const std::string RED = "\033[1;31m";
const std::string DEFAULT = "\033[0m";


console_manager::console_manager() {


}

void console_manager::clear() {
#ifdef _WIN64
	system("cls");
#else
	system("clear");
#endif
}

//accept command as parameter then display the screen
void console_manager::screenCommand_c(const std::string& command) {

	//check if command starts with "screen -r" or "screen -s"
	if (command.rfind("screen -r ", 0) == 0 || command.rfind("screen -s ", 0) == 0) {
		std::string screenName = command.substr(10); //extract the name of the screen from command
		show(screenName); //show the corresponding screen
	}
	else {
		std::cout << RED << "Command not recognized." << "\n" << DEFAULT; //error handling for when user enters anything other than "screen -r or -s"
	}
}

//for getting the timestamp
std::string console_manager::timeStamp() {
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

//display contents of the screen
void console_manager::show(const std::string& screenName) {
	//we should have a list of screens
	//TODO: condition to check if the screen exists or not

	clear();
	std::cout << "Screen: " << "screenName" << "\n"; //TODO: screenName should be a variable
	std::cout << "Content: " << "something in here" << "\n"; //TODO: list of contents for the screen to be displayed  screenContents[screenName]
	std::cout << "Timestamp: " << timeStamp() << "\n";

	//TODO: error handling for when screen name is invalid, list available screens
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