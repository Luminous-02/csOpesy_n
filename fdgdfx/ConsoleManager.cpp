#include "ConsoleManager.h"
#include "ProcessConsole.h" 
#include "MainMenuConsole.h"

ConsoleManager::ConsoleManager(ConfigurationManager& configManager)
    : console(nullptr),
    mainMenuCommandHandler(std::make_unique<MainMenuCommandHandler>(*this)),
    processCommandHandler(std::make_unique<ProcessCommandHandler>(*this)),
    currentCommandHandler(mainMenuCommandHandler.get()),
    initialized(false),
    configManager(configManager){
}

void ConsoleManager::setConsole(Console* newConsole) {
    console = newConsole;
}

void ConsoleManager::displayPrompt() const {
    console->displayPrompt();
}

std::string ConsoleManager::getCommand() const {
    return console->getCommand();
}
 
void ConsoleManager::addProcess(const std::string& processName, std::unique_ptr<Process> process) {
    processes[processName] = std::move(process);
}

void ConsoleManager::createNewProcess(const std::string& processName) {
    system("cls");

    std::cout << "Proces: " << processName << std::endl;
    std::cout << "ID: "; 

    //get the id
    int id;
    std::cin >> id;
    std::cin.ignore();

    std::cout << "\n\n"; 

    std::cout << "Lines of code: ";

    //get the total lines of code
    int totalLines;
    std::cin >> totalLines;
    std::cin.ignore();

    //create the process
    auto process = std::make_unique<Process>(processName, id, totalLines);

    //add to the manager
    addProcess(processName, std::move(process));
}

//for screen -r command
void ConsoleManager::displayProcessScreen(const std::string& processName) {
    
    auto it = processes.find(processName);

    if (it != processes.end()) {
        system("cls");

        //configManager.getNumCpu();
        //scheduler.start();

        ProcessConsole processConsole (it->second.get(), processCommandHandler.get());
        
        currentCommandHandler = processCommandHandler.get(); 
        processConsole.displayProcessConsole();
        processConsole.displayPrompt();
    }
    else {
        std::cout << "Process " << it->second->getName() << "not found.";
    }
}

void ConsoleManager::showMainMenu() {
    
    MainMenuCommandHandler mainMenuCommandHandler(*this);
    
    MainMenuConsole mainMenuConsole(&mainMenuCommandHandler);
    mainMenuCommandHandler.resetExitFlag();
    setConsole(&mainMenuConsole);

    mainMenuConsole.displayPrompt();
}

bool ConsoleManager::isInitialized() const {
    return initialized;
}

void ConsoleManager::setInitialized(bool init) {
    initialized = init; 
}

ConfigurationManager& ConsoleManager::getConfigurationManager() {
    return configManager;
}

std::unordered_map<std::string, std::unique_ptr<Process>>& ConsoleManager::getSchedProcesses() {
    return processes;
}

std::string ConsoleManager::getCurrentProcessName() const {
    std::cout << "this is process " << currentProcessName << std::endl; 
    return currentProcessName;
}

void ConsoleManager::listProcesses() const {
    if (processes.empty()) {
        std::cout << "No processes created yet." << std::endl;
        return;
    }

    std::cout << "Currently stored processes:" << std::endl;
    for (const auto& pair : processes) {
        const Process* process = pair.second.get();
        std::cout << "Process Name: " << process->getName() << std::endl;
        std::cout << "Process ID: " << process->getID() << std::endl;
        std::cout << "Current Line: " << process->getCurrentLine() << std::endl;
        std::cout << "Total Lines: " << process->getTotalLines() << std::endl;
        std::cout << "Status: " << (process->getStatus() == Process::ProcessState::FINISHED ? "Finished" : "Running") << std::endl;
        std::cout << "-------------------------------------" << std::endl;
    }
}