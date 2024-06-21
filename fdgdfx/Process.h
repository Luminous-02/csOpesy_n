#pragma once

#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>

class Process {
private:
	int processID;
	int currentLine;
	int totalLines;
	std::time_t timestamp;

public:
	Process(int id, int current, int total)
		: processID(id), currentLine(current), totalLines(total), timestamp(std::time(nullptr)) {} //initialize

	//get the process ID
	int getProcessID() const {
		return processID;
	}

	int getCurrentLine() const {
		return currentLine;
	}

	int getTotalLines() const {
		return totalLines;
	}

	//timestamp
	std::string getTimeStamp() const {
		std::ostringstream oss;
		std::tm tm;
		localtime_s(&tm, &timestamp); // Use localtime_s instead of localtime
		oss << std::put_time(&tm, "%m/%d/%Y, %I:%M:%S %p");
		return oss.str();
	}

	void incrementCurrentLine() {
		++currentLine;
	}
};