#include "requesthandler.h"

namespace Sylvester {

RequestHandler::RequestHandler()  : _log(GETLOG("REQUEST_HANDLER")) {
	
}

void RequestHandler::handle(struct mg_connection *conn, const struct mg_request_info *request_info) {
	_log.log(LOG_INFO, "Mongoose New Request: %s\n", request_info->uri);
	if (strcmp(request_info->uri, "/graph") == 0) {
		
	} else if (strcmp(request_info->uri, "/config") == 0) {
		
	} else {
		_log.log(LOG_WARN, "Requested unknown path: %s\n", request_info->uri);
	}
}

} /* namespace Sylvester */
