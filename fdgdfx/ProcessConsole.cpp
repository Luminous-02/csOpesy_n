#include "ProcessConsole.h"
#include <iostream>

ProcessConsole::ProcessConsole(Process* process) : process(process) {}

void ProcessConsole::displayProcessConsole() const {
    if (process) {
        std::cout << "Process: " << process->getName() << std::endl;
        std::cout << "ID: " << process->getID() << "\n\n";
        std::cout << "Current instruction line: " << process->getCurrentLine() << std::endl;
        std::cout << "Lines of code: " << process->getTotalLines() << "\n" << std::endl;
    }
}