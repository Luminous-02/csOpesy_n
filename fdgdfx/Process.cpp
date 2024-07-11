#include "Process.h"
#include "PrintCommand.h"

Process::Process(const std::string& name, int id, int totalLines)
	: name(name),
	id(id),
	totalLines(totalLines),
	currentLine(0),
	cpuCoreID(-1),
	arrivalTime(0),
	currentState(ProcessState::READY)
{
initializeCommands();
}

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

void Process::initializeCommands() {
	for (int i = 0; i < totalLines; i++) {
		std::string commandMessage = "Command " + std::to_string(i + 1);
		addCommand(std::make_unique<PrintCommand>(id, commandMessage));
	}
}