#include "ConfigurationManager.h"

#include <fstream>
#include <sstream>
#include <iostream>

//open confi.txt and read the contents
void ConfigurationManager::loadConfig(const std::string& configFilePath) {
	std::ifstream configFile(configFilePath);

	if (configFile.is_open()) {
		std::string line;

		while (std::getline(configFile, line)) {
			std::istringstream iss(line);
			std::string key;
			std::string value;

			if (iss >> key >> value) {
				configParameters[key] = value;
			}
		}
	}
	else {
		std::cerr << "Unable to open config file: " << configFilePath << std::endl; 
	}
}


std::string ConfigurationManager::getConfigParameter(const std::string& key) const {
	auto it = configParameters.find(key);

	if (it != configParameters.end()) {
		return it->second;
	}

	return ""; 
}

int ConfigurationManager::getNumCpu() const {
	return std::stoi(configParameters.at("num-cpu"));
}

int ConfigurationManager::getQuantumCycles() const {
	return std::stoi(configParameters.at("quantum-cycles"));
}

int ConfigurationManager::getMinIns() const {
	return std::stoi(configParameters.at("min-ins"));
}

int ConfigurationManager::getMaxIns() const {
	return std::stoi(configParameters.at("max-ins"));
}

bool ConfigurationManager::isPreemptive() const {
	return std::stoi(configParameters.at("preemptive"));
}

double ConfigurationManager::getDelayPerExec() const {
	return std::stod(configParameters.at("delay-per-exec"));
}

double ConfigurationManager::getBatchProcessFreq() const {
	return std::stod(configParameters.at("batch-process-freq"));
}

std::string ConfigurationManager::getScheduler() const {
	return configParameters.at("scheduler");
}

void ConfigurationManager::printConfig() const {
	for (const auto& pair : configParameters) {
		std::cout << pair.first << ": " << pair.second << std::endl; 
	}
}
