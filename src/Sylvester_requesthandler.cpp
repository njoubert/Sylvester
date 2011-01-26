#include "Sylvester/requesthandler.h"


namespace Sylvester {

RequestHandler::RequestHandler()  : _log(GETLOG("REQUEST_HANDLER")) {
	
}

void RequestHandler::handle(struct mg_connection *conn, const struct mg_request_info *request_info) {
	_log.log(LOG_INFO, "Mongoose New Request: %s\n", request_info->uri);
		if (strcmp(request_info->uri, "/graph") == 0) {
			if (strcmp(request_info->request_method, "POST") == 0) {
			
					// if (mg_get_header)
					// 
					// void* buf = 
		
			} else {
				_log.log(LOG_WARN, "Unsupported request method: %s\n", request_info->request_method);
				handleError(conn, ERR_INCORRECT_METHOD, "Expected but did not receive POST");
			}
		} else if (strcmp(request_info->uri, "/config") == 0) {
		
		
		
		} else {
			_log.log(LOG_WARN, "Requested unknown path: %s\n", request_info->uri);
			handleError(conn, ERR_UNKNOWN_PATH, "Requested an unknown path.");
		}		
}

//sends back error info
void RequestHandler::handleError(struct mg_connection *conn, RESPONSE_ERROR_CODE code, const char* msg) {
	_log.log(LOG_INFO, "Handling Incorrect Request, formulating response...\n");
	JSONErrorResponse res;
	res.setMessage(code, msg);
	res.send(conn);
}
	

} /* namespace Sylvester */
