#pragma once

#include <string>

class CommandHandler
{
public:
	virtual ~CommandHandler() = default;
	virtual void handleCommand(const std::string& command) = 0;
	virtual bool shouldExit() const = 0;
	virtual void resetExitFlag() = 0; 
};

