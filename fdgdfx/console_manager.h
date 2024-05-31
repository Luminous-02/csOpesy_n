#pragma once

#include <iostream>
#include <string>
#include <map>
#include <ctime>

class console_manager {
public:
	console_manager();
	void screenCommand_c(const std::string& command); //screen for the screen -s or screen -r command, pass the command

private:
	std::map<std::string, std::string> content;
	std::string timeStamp();
	void clear();
	void show(const std::string& screenName); //show the corresponding screen
};