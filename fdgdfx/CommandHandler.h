#pragma once

#include <string>

class CommandHandler
{
public:
	virtual ~CommandHandler() = default;
	virtual void handleCommand(const std::string& command) const = 0;
};

