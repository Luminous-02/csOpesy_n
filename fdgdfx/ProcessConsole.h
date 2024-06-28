#pragma once

#include "Process.h"

class ProcessConsole {
public:
	ProcessConsole(Process* process);

	void displayProcessConsole() const;

private:
	Process* process;
};