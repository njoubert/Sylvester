#include "log.h"

namespace Sylvester {
	
Log::Log() {
	_level = LOG_DEBUG;
}

Log::~Log() {
	
}

void Log::setLevel(int level) {
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
	vfprintf(stderr, msg, argp);
	va_end(argp);	
}

} /* namespace Sylvester */
