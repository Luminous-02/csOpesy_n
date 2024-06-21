#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <ctime>

class Process {
private:
    int processID;
    std::vector<std::string> printCommands;

public:

    Process() : processID(0) {}

    Process(int id)
        : processID(id) {}

    void addPrintCommand(const std::string& command) {
        printCommands.push_back(command);
    }

    void executePrintCommands() {
        std::string filename = "process_" + std::to_string(processID) + ".txt";
        std::ofstream outputFile(filename);

        if (outputFile.is_open()) {
            for (const auto& command : printCommands) {
                auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                char timestampBuffer[26];
                ctime_s(timestampBuffer, sizeof(timestampBuffer), &now); // Use ctime_s instead of ctime
                outputFile << "Timestamp: " << timestampBuffer << "Command: " << command << "\n";
            }
            outputFile.close();
        }
        else {
            std::cerr << "Unable to open file: " << filename << std::endl;
        }
    }

    int getProcessID() const {
        return processID;
    }

    const std::vector<std::string>& getPrintCommands() const {
        return printCommands;
    }

    void printSchedule() const {
        std::cout << "Schedule for Process " << processID << ":\n";
        for (const auto& command : printCommands) {
            std::cout << "  " << command << "\n";
        }
    }
};
