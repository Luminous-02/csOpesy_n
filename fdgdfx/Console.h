#pragma once

#include <string>
class Console
{
public:
	virtual ~Console() = default;
	virtual void displayPrompt() const = 0;
	virtual std::string getCommand() const = 0;

};

