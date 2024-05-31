#include "command_handler.h"
#include "console_manager.h"

int main()
{
    console_manager cm; //console manager instance
    std::string command;

    printHeader();

    //while loop until user exits
    while (true) {

        //TODO: fix the exit thing, "exit" in screen -s or screen -r console == back to main menu, not exit the whole program

        //input
        std::cout << "Enter Command: ";
        std::getline(std::cin, command); //get the whole input line

        if (command == "exit") {
            break; // Exit the loop and end the program
        }
        else if (command == "clear") {
            clear();
        }
        else {
            cm.screenCommand_c(command);
        }

        /*
        else if (command == "marquee") {
            marquee();
        }
        else if (command == "screen") {
            screen(); //list all the screens
        }
        else if (command == "process-smi") {
            processsmi();
        }
        else if (command == "nvidia-smi") {
            nvidiasmi();
        }
        else {
            std::cout << "Invalid command. Please try again.\n";
        }
        */
    }

    return 0;
}