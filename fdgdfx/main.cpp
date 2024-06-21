
#include <iostream>
#include "Console.h"
#include <vector>
/*

int main()
{
	MainMenuConsole mainMenu;
	//Process process1(1, 1, 10);

	//mainMenu.addProcessConsole("process1", process1);

	mainMenu.run();
	return 0;
}*/

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

// main.cpp


int main() {
	const int NUM_PROCESSES = 10;
	const int NUM_PRINT_COMMANDS = 100;
	const int NUM_CORES = 4;

	MainMenuConsole mainMenu;

	//std::vector<Process> processes;

	for (int i = 1; i <= NUM_PROCESSES; i++) {
		Process process(i);

		for (int j = 1; j <= NUM_PRINT_COMMANDS; j++) {
			std::string command = "Print command " + std::to_string(j) + " for Process " + std::to_string(i);
			process.addPrintCommand(command);
		}

		//processes.push_back(process);
		/*
		for (auto& process : processes) {
			process.executePrintCommands();
		}*/

		mainMenu.addProcess(i, process); 
	}

	mainMenu.run();

	return 0; 
}