#include "ConfigurationManager.h"

#include <fstream>
#include <sstream>
#include <iostream>

void ConfigurationManager::trim(std::string& str) {
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), str.end());
}

void ConfigurationManager::loadConfig(const std::string& configFilePath) {
    std::ifstream configFile(configFilePath);

    if (configFile.is_open()) {
        std::string line;

        while (std::getline(configFile, line)) {
            std::istringstream iss(line);
            std::string key;
            std::string value;

            if (std::getline(iss, key, ' ') && std::getline(iss, value)) {
                trim(key);
                trim(value);

                // Remove quotes from around the value
                if (value.front() == '\"' && value.back() == '\"') {
                    value = value.substr(1, value.length() - 2);
                }

                // Check if the key is not empty before adding to the map
                if (!key.empty()) {
                    configParameters[key] = value;
                }

                // Debug output
               // std::cout << "Read key: " << key << " with value: " << value << std::endl;
            }
        }
    } else {
        std::cerr << "Unable to open config file: " << configFilePath << std::endl;
    }
}

std::string ConfigurationManager::getConfigParameter(const std::string& key) const {
    auto it = configParameters.find(key);

    if (it != configParameters.end()) {
        return it->second;
    }

    std::cerr << "Key not found: " << key << std::endl;

    return "";
}

int ConfigurationManager::getNumCpu() const {
    return getParameterAsInt("num-cpu");
}

int ConfigurationManager::getQuantumCycles() const {
    return getParameterAsInt("quantum-cycles");
}

int ConfigurationManager::getMinIns() const {
    return getParameterAsInt("min-ins");
}

int ConfigurationManager::getMaxIns() const {
    return getParameterAsInt("max-ins");
}

bool ConfigurationManager::isPreemptive() const {
    return getParameterAsInt("preemptive") != 0;
}

double ConfigurationManager::getDelayPerExec() const {
    return getParameterAsDouble("delay-per-exec");
}

double ConfigurationManager::getBatchProcessFreq() const {
    return getParameterAsDouble("batch-process-freq");
}

std::string ConfigurationManager::getScheduler() const {
    return getParameterAsString("scheduler");
}

void ConfigurationManager::printConfig() const {
    for (const auto& pair : configParameters) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}

int ConfigurationManager::getParameterAsInt(const std::string& key) const {
    auto it = configParameters.find(key);
    if (it != configParameters.end()) {
       // std::cout << "found it!\n";
        return std::stoi(it->second);
    } else {
        std::cerr << "Can't find: " << key << std::endl;
        return -1;
    }
}

double ConfigurationManager::getParameterAsDouble(const std::string& key) const {
    auto it = configParameters.find(key);
    if (it != configParameters.end()) {
       // std::cout << "found it!";
        return std::stod(it->second);
    } else {
        std::cerr << "Key not found: " << key << std::endl;
        return -1.0;  // Default value or handle error as appropriate
    }
}

std::string ConfigurationManager::getParameterAsString(const std::string& key) const {
    auto it = configParameters.find(key);
    if (it != configParameters.end()) {
        return it->second;
    } else {
        std::cerr << "Key not found: " << key << std::endl;
        return "";  // Default value or handle error as appropriate
    }
}
