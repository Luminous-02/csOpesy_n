#include "Process.h"

Process::Process(const std::string& name, int id, int totalLines)
	: name(name), id(id), currentLine(1), totalLines(totalLines), status(Status::Running) {}

const std::string& Process::getName() const {
	return name;
}

int Process::getID() const {
	return id;
}

//start at line 1
int Process::getCurrentLine() const {
	return currentLine;
}

int Process::getTotalLines() const {
	return totalLines;
}

Process::Status Process::getStatus() const {
	return status;
}

//simulate running the process
void Process::runProcess() {
	if (currentLine <= totalLines) {
		//status is running by default
		currentLine++;
	}
	else {
		status = Status::Finished;
	}
}