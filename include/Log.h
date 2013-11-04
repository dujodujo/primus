#ifndef LOG_H
#define LOG_H

#include <sstream>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

class Log {

protected:
	static std::string fileName;

public:
	static void createLog(std::ostringstream& txt);
	static bool log(const std::ostringstream& oss);
};

#endif