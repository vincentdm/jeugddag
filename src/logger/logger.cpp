/*
 * logger.cpp
 *
 *  Created on: 26-mrt.-2013
 *      Author: vincent
 */

#include "logger.h"
#include <stdio.h>

namespace Logger {

Logger * Logger::logger = NULL;
Logger::Logger() {
	// TODO Auto-generated constructor stub

}

Logger::~Logger() {
	// TODO Auto-generated destructor stub
}

void Logger::LogMessage(int level,std::string className, std::string message,va_list lst) {

	std::string format = std::string("[") + std::string(logLevels[level]) + std::string("]") + className + std::string("::") + message + std::string("\n");

	vprintf(format.c_str(),lst);
}

Logger * Logger::GetInstance() {
	if(Logger::logger == NULL)
		logger = new Logger();
	return Logger::logger;
}

} /* namespace Logger */
