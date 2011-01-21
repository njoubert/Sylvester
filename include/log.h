//
//  server.h
//
//  Created by Niels Joubert on 2011-01-21.
//

#ifndef SYLVERSER_SERVER_H_
#define SYLVERSER_SERVER_H_

#include <iostream>
#include "singleton.h"

namespace Sylvester {

//
// Logging class.
// Level 5 is highest level (most logging, default)
// Level 0 is OFF (no logging)
class Log {
public:
	Log();
	~Log();
	void setLevel(int level);
	void log(int level, ...);
private:
	int _level;
};

typedef Singleton<Log> LOG;
	
}


#endif /* SYLVERSER_SERVER_H_ */