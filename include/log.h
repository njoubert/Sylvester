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

#define LOG Singleton<Log>::Instance()

namespace Sylvester {

enum LOGLEVEL {
	LOG_OFF = 0,
	LOG_ERROR = 1,
	LOG_MESSAGE = 2,
	LOG_WARN = 3,
	LOG_STATUS = 4,
	LOG_INFO = 5,
	LOG_DEBUG = 6
};

class Log {
public:
	Log();
	~Log();
	void setLevel(int level);
	void log(LOGLEVEL level, char* msg, ...);
private:
	int _level;
};
	
}


#endif /* SYLVERSER_LOG_H_ */