#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "Process.h"

class Scheduler {
private:
    //std::vector<Process> processes;
    //std::vector<std::thread> workerThreads;

    std::vector<Process>& processes;
    int numCores;
    int nextProcessIndex;
    std::mutex mtx;
    std::condition_variable cv;
    bool finished;

public:
    void addProcess(const Process& process) {
        processes.push_back(process);
    }

    /*
    void runScheduler() {
        // Start a worker thread for each process
        for (auto& process : processes) {
            workerThreads.emplace_back(&Process::executePrintCommands, &process);
        }

        // Join all worker threads to wait for them to complete
        for (auto& thread : workerThreads) {
            thread.join();
        }
    }*/

    void run() {
        std::thread cpuWorker(&Scheduler::cpuWorkerThread, this);
        cpuWorker.detach(); // Detach the CPU worker thread to run independently

        while (!finished) {
            std::unique_lock<std::mutex> lck(mtx);
            cv.wait(lck, [this]() { return nextProcessIndex < processes.size(); });

            if (nextProcessIndex < processes.size()) {
                int currentIndex = nextProcessIndex++;
                lck.unlock();

                for (int core = 1; core <= numCores; ++core) {
                    std::thread worker(&Process::executePrintCommands, &processes[currentIndex], core);
                    worker.detach(); // Detach the worker thread to run independently
                }
            }
            else {
                finished = true;
            }
        }
    }

    void cpuWorkerThread() {
        while (!finished) {
            std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate CPU work
        }
    }
};
