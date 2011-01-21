#include "log.h"

namespace Sylvester {
	
Log::Log() {
	std::cout << "Log initialized" << std::endl;
	_level = 5;
}

Log::~Log() {
	
}

void Log::setLevel(int level) {
	if (level > 5)
		level = 5;
	if (level < 0)
		level = 0;
	_level = level;
}

void Log::log(int level, ...) {
	
}
} /* namespace Sylvester */
