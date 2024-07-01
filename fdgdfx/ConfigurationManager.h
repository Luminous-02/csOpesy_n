#pragma once

#include <map>
#include <string>

class ConfigurationManager
{
public:
	void loadConfig(const std::string& configFilePath);
	std::string getConfigParameter(const std::string& key) const;

	//comment this out 
	void printConfig() const; 

	int getNumCpu() const;
	std::string getScheduler() const;
	int getQuantumCycles() const;
	bool isPreemptive() const;
	double getBatchProcessFreq() const;
	int getMinIns() const;
	int getMaxIns() const;
	double getDelayPerExec() const; 

private:
	std::map<std::string, std::string> configParameters; 
};

