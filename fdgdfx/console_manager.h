#pragma once

#include <iostream>
#include <string>
#include <map>
#include <ctime>

extern const std::string RED;
extern const std::string DEFAULT;

class console_manager
{
public:
	console_manager();
	void clear();
	void screenCommand_c(const std::string &command);
	std::string timeStamp();
	void show(const std::string &screenName);

private:
	std::map<std::string, std::string> screenContents; // Map to store screen contents
	std::string currentScreen;						   // Track the current screen

	// Other private members (timeStamp(), etc.) remain unchanged

	void initializeMainScreen()
	{
		// Initialize the "mainScreen" content here
		screenContents["mainScreen"] = "Welcome to the main screen!";
		currentScreen = "mainScreen"; // Set the initial screen
	}
};
