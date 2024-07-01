#pragma once

#include "Console.h"
#include "Process.h"
#include "ProcessCommandHandler.h"

class ProcessConsole : public Console {
public:
	ProcessConsole(Process* process, ProcessCommandHandler* handler);

	void displayPrompt() const override;
	std::string getCommand() const override;

	void displayProcessConsole() const;

private:
	Process* process;
	ProcessCommandHandler* handler;
};