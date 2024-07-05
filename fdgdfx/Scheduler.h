#pragma once

#include "ConfigurationManager.h"
#include "Process.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <thread>
#include <atomic>
#include <queue>
#include <mutex>

class Scheduler {
public:
	Scheduler(int numCore, const std::string& algorithm, int quantumCycles, bool preemptive,
			  std::unordered_map<std::string, std::unique_ptr<Process>>& processes);

	~Scheduler();

	void start();
	void stop();

private:
	int numCores;
	std::string algorithm;
	bool preemptive;
	int quantumCycles; 

	ConfigurationManager configManager; 

	std::vector<std::thread> workers;
	std::unordered_map<std::string, std::unique_ptr<Process>>& processes;

	std::atomic<bool> shouldStop;

	void workerFunction(int coreId); 
	void scheduleFCFS();

	std::queue<Process*> processQueue;
	std::mutex queueMutex;
	std::condition_variable cv;

	std::vector<bool> coreBusy;

	//add the other members later

	//void runAlgorithm(); 
};