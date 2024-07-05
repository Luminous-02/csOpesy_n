#pragma once

#include <map>
#include <string>
#include <unordered_map>

class ConfigurationManager
{
public:
	void trim(std::string& str);
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
	int getParameterAsInt(const std::string& key) const;
	double getParameterAsDouble(const std::string& key) const;
	std::string getParameterAsString(const std::string& key) const;

	std::map<std::string, std::string> configParameters; 
	
};

