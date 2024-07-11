#pragma once

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "ICommand.h"

class ICommand; 

class Process {
public:
	enum class ProcessState {
		READY,
		RUNNING,
		WAITING,
		FINISHED
	};

	Process(const std::string& name, int id, int totalLines);

	const std::string& getName() const;
	int getID() const;
	int getCurrentLine() const;
	ProcessState getStatus() const;
	//int getArrivalTime() const;
	int getTotalLines() const;
	
	void addCommand(std::unique_ptr<ICommand> command);
	void runProcess(); 

	void initializeCommands();
	

private:
	std::string name;

	int id;
	int currentLine;
	int totalLines;
	int cpuCoreID;

	int arrivalTime; 

	ProcessState currentState;

	std::vector < std::shared_ptr<ICommand>> commandList;
};