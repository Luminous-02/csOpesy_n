#include "PrintCommand.h"

PrintCommand::PrintCommand(int pid, const std::string& toPrint)
	: ICommand(pid, CommandType::PRINT), toPrint(toPrint){}

void PrintCommand::execute() {
	std::cout << "Process " << pid << ": " << toPrint << std::endl;
}