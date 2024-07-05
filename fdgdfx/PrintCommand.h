#pragma once

#include "ICommand.h"
#include <string>
#include <iostream>

class PrintCommand : public ICommand
{
public:
	PrintCommand(int pid, const std::string& toPrint);
	void execute() override;

private:
	std::string toPrint; 
};

