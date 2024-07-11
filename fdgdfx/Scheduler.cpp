#include "Scheduler.h"

#include <iostream>
#include <chrono>

Scheduler::Scheduler(int numCores, const std::string& algorithm, int quantumCycles, bool preemptive,
			std::unordered_map<std::string, std::unique_ptr<Process>>& processes) //, const std::string& algorithm, bool preemptive, int quantumCycles)
	: numCores(numCores),
	  algorithm(algorithm),
	  quantumCycles(quantumCycles), 
      preemptive(preemptive),
	  processes(processes),
	  shouldStop(false),
	  coreBusy(numCores, false){}

Scheduler::~Scheduler() {
	stop();
}

void Scheduler::start() {

}

void Scheduler::scheduleFCFS() {
}

void Scheduler::workerFunction(int coreId) {
	//std::cout << "Core " << coreId << "Started executing tasks\n" << std::endl; 
}

void Scheduler::stop() {

}

void Scheduler::executeProcess(Process* process) {
	if (!process) return;

	std::thread processThread([process]() {

		process->runProcess();
		});

	processThread.detach();
}