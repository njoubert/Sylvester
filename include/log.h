//
//  server.h
//
//  Created by Niels Joubert on 2011-01-21.
//

#ifndef SYLVERSER_LOG_H_
#define SYLVERSER_LOG_H_

#include "singleton.h"
#include <stdio.h>
#include <stdarg.h>
#include <map>
#include <string>

#define GETLOG(className) Singleton<LogFactory>::Instance().getLog(className)


namespace Sylvester {

using namespace std;

enum LOGLEVEL {
	LOG_OFF = 0,     //don't log ANYTHING
	LOG_ERROR = 1,   //something fucked up
	LOG_MESSAGE = 2, //message to the user, not inside loop
	LOG_WARN = 3,
	LOG_STATUS = 4,  //status of system, periodic but not often
	LOG_INFO = 5,
	LOG_DEBUG = 6
};

class Log {
public:
	Log();
	Log(string className, LOGLEVEL level);
	~Log();
	void setLevel(LOGLEVEL level);
	void log(LOGLEVEL level, char* msg, ...);
private:
	string _className;
	LOGLEVEL _level;
};

class LogFactory {
public:
	LogFactory();
	~LogFactory();
	Log& getLog(string className);
	void setDefaultLevel(LOGLEVEL level);
	
private:
	LOGLEVEL _level;
	map<string, Log> logs;
};

}


#endif /* SYLVERSER_LOG_H_ */