#pragma once

#include <string>
#include <iostream>

class CommandHandler {
public:
	void handleCommand(const std::string& command) {
		if (command.find("screen -s") == 0 || command.find("screen -r") == 0) {
			std::string screenName = command.substr(10);
		}
		else if (command == "exit") {

		}
		else {
			std::cout << "Command not recognized: " << command << "\n";
		}
	}
};