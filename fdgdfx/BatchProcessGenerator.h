#pragma once

#include "ConsoleManager.h"
#include <thread>
#include <atomic>
class BatchProcessGenerator
{

public: 
	BatchProcessGenerator(ConsoleManager& consoleManager, float processGenFreq);
	~BatchProcessGenerator();

	void start();
	void stop();

private:
	ConsoleManager& consoleManager;
	float processGenFreq;
	std::atomic<bool> running; 
	std::thread generatorThread;

	void generate(); 
};
