/*
 * logger.h
 *
 *  Created on: 26-mrt.-2013
 *      Author: vincent
 */

#ifndef LOGGER_H_
#define LOGGER_H_


#define LOG_DEBUG    0
#define LOG_INFO     1
#define LOG_WARNING  2
#define LOG_ERROR    3
#define LOG_CRITICAL 4

#ifndef LOGGER_MINLEVEL
#  define LOGGER_MINLEVEL LOG_DEBUG
#endif

#ifndef LOGGER_DISABLED

#include <string>
#include <stdarg.h>
using std::string;
namespace Logger {


static char* logLevels[] = {"DEBUG","INFO","WARNING","ERROR","CRITICAL" };

#ifndef LOGGER_CLASSNAME
#  define LOGGER_CLASSNAME "unknown"
#endif

class Logger {
public:
	Logger();
	virtual ~Logger();

	void LogMessage(int level, std::string className, std::string message,va_list lst);

	static Logger * GetInstance();
private:
	static Logger * logger;
};




} /* namespace Logger */

#endif

namespace Logger {
inline void Log(int level,std::string message,...) {
#ifndef LOGGER_DISABLED


	va_list lst;
	va_start(lst,message.c_str());

	Logger::GetInstance()->LogMessage(level,LOGGER_CLASSNAME,message,lst);
	va_end(lst);
#endif
}
}


#endif /* LOGGER_H_ */
