#include <iostream>
#include "Console.h"

int main()
{
	MainMenuConsole mainMenu;
	//Process process1(1, 1, 10);

	//mainMenu.addProcessConsole("process1", process1);

	mainMenu.run();
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