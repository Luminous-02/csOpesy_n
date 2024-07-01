#pragma once

#include "CommandHandler.h"

class ConsoleManager;

class ProcessCommandHandler :
    public CommandHandler
{
public:
    ProcessCommandHandler(ConsoleManager& consoleManager);

    void handleCommand(const std::string& command) const override;
    bool shouldExit() const override;

    void resetExitFlag() override;

private:
    ConsoleManager& consoleManager; 
    mutable bool exit = false; 
};

