#include "ProcessConsole.h"
#include <iostream>

ProcessConsole::ProcessConsole(Process* process, ProcessCommandHandler* handler) 
    : process(process), handler(handler){}

void ProcessConsole::displayPrompt() const {

    while (true) {
        std::cout << "Enter Command: ";
        std::string command = getCommand();

        handler->handleCommand(command);

        if (handler->shouldExit()) {
            break; 
       }
    }
}

std::string  ProcessConsole::getCommand() const {
    std::string command;
    std::getline(std::cin, command);
    return command;
}

void ProcessConsole::displayProcessConsole() const {
    if (process) {
        std::cout << "Process: " << process->getName() << std::endl;
        std::cout << "ID: " << process->getID() << "\n\n";
        std::cout << "Current instruction line: " << process->getCurrentLine() << std::endl;
        std::cout << "Lines of code: " << process->getTotalLines() << "\n" << std::endl;
    }
}