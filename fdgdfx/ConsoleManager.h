#pragma once

#include "Console.h"
#include "Process.h"

#include <iostream>
#include <map>
#include <memory>



class ConsoleManager
{
public:
	ConsoleManager();
	ConsoleManager(Console* console);
	void displayPrompt() const; //mainmenu
	std::string getCommand() const;

	void addProcess(const std::string& processName, std::unique_ptr<Process> process);
	void displayProcessScreen(const std::string& processName);
	//void reportUtil() const;

private:
	Console* console;

	std::map<std::string, std::unique_ptr<Process>> processes;
};

