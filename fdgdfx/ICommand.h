#pragma once

#include <string>

class ICommand
{
public:

	enum CommandType {
		IO,
		PRINT
	};

	CommandType getCommandType() const;
	ICommand(int pid, CommandType commandType);

	virtual ~ICommand() = default;
	virtual void execute() = 0;

protected:
	int pid;
	CommandType commandType;
};

