#pragma once

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <thread>
#include <mutex>
#include "Process.h"
#include "CommandHandler.h"
#include "static.h"

class Console {
private:
	std::string consoleName;

public:
	Console(const std::string& name)
		: consoleName(name) {}

	//this will be overidden by thhe derived class
	virtual ~Console() = default;

	virtual void displayHeader() const {
		return printHeader();
	}

	virtual std::string getCommand() {
		std::string command;
		std::cout << "Enter command: ";
		std::getline(std::cin, command);
		return command;
	}
};

class MainMenuConsole : public Console {
private:

	CommandHandler commandHandler;
	std::map<int, Process> processes;
	int numCores;

	//std::map<std::string, ProcessConsole> processConsoles;

public:
	MainMenuConsole() : Console("Main Menu") {}

	//MainMenuConsole(int cores) : Console("Main Menu") {}

	void addProcess(int id, const Process& process) {
		processes[id] = process;
	}

	void displaySchedules() const {
		std::cout << "Running processes: ";
		for (const auto& pair : processes) {
			pair.second.printSchedule();
			std::cout << "\n";
		}
	}

	void scheduleProcesses() {
		std::vector<std::thread> threads;
		std::mutex mtx;

		int coreIndex = 0; // Initialize core index

		for (auto& pair : processes) {
			threads.emplace_back([&]() {
				std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate processing time
				mtx.lock();
				std::cout << "Process " << pair.first << " scheduled on CPU core " << coreIndex << "\n";
				mtx.unlock();
				coreIndex = (coreIndex + 1) % numCores; // Move to the next core circularly
				});
		}

		for (auto& thread : threads) {
			thread.join();
		}
	}

	/*void addProcessConsole(const std::string& name, Process process) {
		processConsoles[name] = ProcessConsole(name, process);
	}*/

	void run() {
		displayHeader();

		while (true) {
			std::string command = getCommand();
			commandHandler.handleCommand(command);

			if (command == "screen -ls") {
				displaySchedules();
			}
			else if (command == "exit") {
				std::cout << "Exiting...\n";
				break;
			}
			else {
				std::cout << "Command not recognized.\n";
			}
			/*

			if (command.find("screen -r") == 0 || command.find("screen -s") == 0) {
				std::string screenName = command.substr(10);

				if (processConsoles.find(screenName) != processConsoles.end()){
					processConsoles[screenName].run();
				}
				else {
					std::cout << "Process not found: " << screenName << "\n";
				}
			}*/
		}
	}
};

/*
class ProcessConsole : public Console {
private:
	Process process;

public:
	ProcessConsole(const std::string& name, Process process)
		: Console(name), process(process) {}

	void displayHeader() const override {
		std::cout << "Process Name: " << consoleName << "\n";
		std::cout << "Current Line: " << process.getCurrentLine() << " / " << process.getTotalLines() << "\n";
		std::cout << "TImestamp: " << process.getTimeStamp() << "\n";
	}

	void run() {
		while (true) {
			displayHeader();
			std::string command = getCommand();

			if (command == "exit") {
				std::cout << "Returning to main menu...\n";
				break;
			}
		}
	}
};*/