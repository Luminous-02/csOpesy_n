#include "command_handler.h"
#include "console_manager.h"

int main()
{
    console_manager cm; // Console manager instance
    std::string command;

    printHeader();

    // While loop until user exits
    while (true)
    {
        std::cout << "Enter Command: ";
        std::getline(std::cin, command); // Get the whole input line

        // The "exit" command is now handled inside the screenCommand_c method
        cm.screenCommand_c(command);
    }

    return 0;
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

}

return 0;
}*/