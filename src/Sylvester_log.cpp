#include "log.h"

namespace Sylvester {

LogFactory::LogFactory() {
	_level = LOG_DEBUG;
}
LogFactory::~LogFactory() {
	
}
Log& LogFactory::getLog(string className) {
	if (logs.count(className) > 0) 
		return logs[className];
	if(14 > className.size())
        className.insert(className.size(), 12 - className.size(), ' ');
	Log l(className, _level);
	logs[className] = l;
	return logs[className];
}

void LogFactory::setAllLogLevel(LOGLEVEL level) {
	setDefaultLevel(level);
	map<string, Log>::iterator it;

	for ( it=logs.begin() ; it != logs.end(); it++ ) {
		(*it).second.setLevel(level);
		printf("Setting loglevel for log %s\n", (*it).first.c_str());
	}

}

void LogFactory::setDefaultLevel(LOGLEVEL level) {
	if (level > LOG_DEBUG)
		level = LOG_DEBUG;
	if (level < LOG_OFF)
		level = LOG_OFF;
	_level = level;
}	

Log::Log() {
	_level = LOG_DEBUG;
	_className = "";
}
Log::Log(string className, LOGLEVEL level) {
	_level = level;
	_className = className;
}

Log::~Log() {
	
}

void Log::setLevel(LOGLEVEL level) {
	if (level > LOG_DEBUG)
		level = LOG_DEBUG;
	if (level < LOG_OFF)
		level = LOG_OFF;
	_level = level;
}

//uses printf-style formatting
void Log::log(LOGLEVEL level, char* msg, ...) {
	if (level > _level)
		return;
	
	va_list argp;
	va_start(argp, msg);
	printf("%s ", _className.c_str());
	fflush(stdout);
	vfprintf(stderr, msg, argp);
	va_end(argp);	
}

} /* namespace Sylvester */
