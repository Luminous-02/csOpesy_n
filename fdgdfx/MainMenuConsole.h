#pragma once
#include "Console.h"
#include "MainMenuCommandHandler.h" //since MainMenuConsole will be using MainMenuCommandHandler

class MainMenuConsole :
    public Console
{
public:
    MainMenuConsole(MainMenuCommandHandler* handler);
    void displayPrompt() const override;
    std::string getCommand() const override;

private:
    MainMenuCommandHandler* handler;
};

