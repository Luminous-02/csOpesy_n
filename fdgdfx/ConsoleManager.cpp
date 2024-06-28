#include "ConsoleManager.h"
#include "ProcessConsole.h" 

ConsoleManager::ConsoleManager() : console(nullptr) {}
ConsoleManager::ConsoleManager(Console* console) : console(console) {}

void ConsoleManager::displayPrompt() const {
    console->displayPrompt();
}

std::string ConsoleManager::getCommand() const {
    return console->getCommand();
}

void ConsoleManager::addProcess(const std::string& processName, std::unique_ptr<Process> process) {
    processes[processName] = std::move(process);
}

void ConsoleManager::displayProcessScreen(const std::string& processName) {

    auto it = processes.find(processName);

    if (it != processes.end()) {
        system("cls");

        ProcessConsole processConsole(it->second.get());
        processConsole.displayProcessConsole();
    }
    else {
        std::cout << "Process " << it->second->getName() << "not found.";
    }
}