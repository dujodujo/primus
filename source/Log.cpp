#include "Log.h"

std::string Log::fileName = "log.txt";

void Log::createLog(std::ostringstream& txt) {
	std::ostringstream oss; 
	Log::log((std::ostringstream&) (oss << txt.str()));
}

bool Log::log(const std::ostringstream& oss) {
	std::ofstream ofs(Log::fileName.c_str(), std::ios::out | std::ios::app);
    if (ofs.fail())
		return false;
    if (!(ofs << oss.str() << std::endl)) {
        ofs.close();
        return false;
	}
    ofs.close();
	return true;
}