#pragma once

#include <string>
#include <iostream>

class Process
{
public:
	enum class Status {
		Running,
		Finished
	};

	Process(const std::string& name, int id, int lines);

	const std::string& getName() const;
	int getID() const;
	int getCurrentLine() const;
	int getTotalLines() const;
	Status getStatus() const;

	void runProcess(); //simulate running a process

private:
	std::string name;

	int id;
	int currentLine;
	int totalLines;
	Status status;


};

