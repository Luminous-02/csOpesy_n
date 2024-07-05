#include "Process.h"

Process::Process(const std::string& name, int id, int totalLines)
	: name(name),
	id(id),
	totalLines(totalLines),
	currentLine(0),
	cpuCoreID(-1),
	arrivalTime(arrivalTime),
	currentState(ProcessState::READY){}

const std::string& Process::getName() const {
	return name;
}

int Process::getID() const {
	return id;
}

int Process::getCurrentLine() const {
	return currentLine;
}

int Process::getTotalLines() const {
	return totalLines;
}

Process::ProcessState Process::getStatus() const {
	return currentState;
}

/*
int Process::getArrivalTime() const {
	return arrivalTime; 
}*/

void Process::addCommand(std::unique_ptr<ICommand> command) {
	commandList.push_back(std::move(command));
}

void Process::runProcess() {
	if (currentState == ProcessState::READY || currentState == ProcessState::WAITING) {
		currentState = ProcessState::RUNNING;
	}


	std::cout << "Running process: " << name << " ID: " << id << std::endl;
	while (currentLine < totalLines) {
		if (currentLine < commandList.size()) {
			commandList[currentLine]->execute();
		}

		++currentLine;
	}

	if (currentLine >= totalLines) {
		currentState = ProcessState::FINISHED; 
		std::cout << "Process " << name << " ID: " << id << " finished execution." << std::endl;
	}
}
