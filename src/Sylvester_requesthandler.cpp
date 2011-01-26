#include "Sylvester/requesthandler.h"


namespace Sylvester {

RequestHandler::RequestHandler()  : _log(GETLOG("REQUEST_HANDLER")) {
	
}

void RequestHandler::handle(struct mg_connection *conn, const struct mg_request_info *request_info) {
	_log.log(LOG_INFO, "Mongoose New Request: %s\n", request_info->uri);
		if (strcmp(request_info->uri, "/graph") == 0) {
			//God, Please forgive me for writing this
			if (strcmp(request_info->request_method, "POST") != 0) {
				handleError(conn, ERR_INCORRECT_METHOD_POST, request_info->request_method);		
			} else if (mg_get_header(conn,"Content-Type") == NULL) { //content-type
				handleError(conn, ERR_NO_CONTENT_TYPE, NULL);	
			} else if (strcmp(mg_get_header(conn,"Content-Type"), "application/x-javascript") != 0) {
				handleError(conn, ERR_WRONG_CONTENT_TYPE_JAVASCRIPT, mg_get_header(conn,"Content-Type"));					
			} else if (mg_get_header(conn,"Content-Length") == NULL) {
				handleError(conn, ERR_NO_CONTENT_LENGTH,NULL);
			} else {
				
				int contentLength = atoi(mg_get_header(conn,"Content-Length"));
				char* bodyData = (char*) malloc(sizeof(char)*contentLength);
				
				if (bodyData == NULL) {
					_log.log(LOG_ERROR, "Could not malloc bodyData for received request.\n");
					handleError(conn, ERR_MAJOR_SERVER_ERROR, "Could not malloc bodyData for received request.");		
				}
				
				
			}
			
		} else if (strcmp(request_info->uri, "/config") == 0) {
		
		
		
		} else {
			handleError(conn, ERR_UNKNOWN_PATH, request_info->uri);
		}		
}

//sends back error info
//problem can be null.
void RequestHandler::handleError(struct mg_connection *conn, RESPONSE_ERROR_CODE code, const char* problem) {
	JSONErrorResponse res;
	res.setMessage(code, problem);
	res.send(conn);
}
	

} /* namespace Sylvester */
