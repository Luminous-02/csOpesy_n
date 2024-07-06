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
	//std::cout << "Starting scheduler with " << numCores << " cores and algorithm: " << algorithm << std::endl;
	//std::cout << "Scheduler has " << quantumCycles << "quantum cycles and is " << preemptive << std::endl;

	if (algorithm == "fcfs") {
		scheduleFCFS();
	}

	for (int i = 0; i < numCores; i++) {
		workers.emplace_back(&Scheduler::workerFunction, this, i);
	}

}

void Scheduler::scheduleFCFS() {
	std::lock_guard<std::mutex> lock(queueMutex);

	for (auto& [processName, process] : processes) {
		processQueue.push(process.get());
	}

	cv.notify_all(); 
}

void Scheduler::workerFunction(int coreId) {
	//std::cout << "Core " << coreId << "Started executing tasks\n" << std::endl; 

	while (!shouldStop) {

		Process* process = nullptr;

		{
			std::unique_lock<std::mutex> lock(queueMutex);

			cv.wait(lock, [this]() { return !processQueue.empty() || shouldStop; });

			if (shouldStop) break;

			if (!processQueue.empty()) {
				process = processQueue.front();
				processQueue.pop();
				coreBusy[coreId] = true; 
			}
		}

		if (process) {
			//std::cout << "Core " << coreId << " is process: " << process->getName() << "with ID: " << process->getID() << std::endl;

			process->runProcess(); 

			{
				std::lock_guard<std::mutex> lock(queueMutex);
				coreBusy[coreId] = false; 
			}

			cv.notify_all(); 
		}
		else {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}
}

void Scheduler::stop() {
	shouldStop = true;
	cv.notify_all();

	for (auto& worker : workers) {
		if (worker.joinable()) {
			worker.join();
		}
	}

	std::cout << "Scheduler stopped." << std::endl;
}