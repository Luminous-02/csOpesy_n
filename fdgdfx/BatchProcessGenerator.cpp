#include "BatchProcessGenerator.h"
#include <iostream>
#include <chrono>
#include <sstream>
#include <iomanip>

BatchProcessGenerator::BatchProcessGenerator(ConsoleManager& consoleManager, float processGenFreq)
    : consoleManager(consoleManager), processGenFreq(processGenFreq), running(false) {}

BatchProcessGenerator::~BatchProcessGenerator() {
    stop();
}

void BatchProcessGenerator::start() {
    running = true;
    generatorThread = std::thread(&BatchProcessGenerator::generate, this);
}

void BatchProcessGenerator::stop() {
    running = false;
    if (generatorThread.joinable()) {
        generatorThread.join();
    }
}

void BatchProcessGenerator::generate() {
    int processCount = 0;
    while (running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(processGenFreq * 1000)));

        std::stringstream processName;
        processName << "Process_" << ++processCount;

        // Create a new process
        consoleManager.createNewProcess(processName.str());

        std::cout << "Generated new process: " << processName.str() << std::endl;
    }
}