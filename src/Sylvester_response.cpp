#include "Sylvester/response.h"
#include <sstream>



namespace Sylvester {

using namespace ::Json;
	
void Response::sendHTTPResponse(struct mg_connection *conn, const char* str, size_t len) {
	static const char *ajax_reply_start =
		"HTTP/1.1 200 OK\r\n"
		"Cache: no-cache\r\n"
		"Content-Type: application/x-javascript\r\n";
	mg_printf(conn, "%sContent-Length:%d\r\n\r\n", ajax_reply_start, len);
	mg_printf(conn, str);
	mg_printf(conn, "\r\n");
}

void JSONResponse::sendJSON(struct mg_connection *conn, const Value& value) {
	StyledWriter writer; 	//todo(njoubert): Replace with FastWriter for production
	string out = writer.write(value);
	sendHTTPResponse(conn, out.c_str(), out.length());
}

void JSONErrorResponse::send(struct mg_connection *conn) {
	Value root;
	Value error;
	error["code"] = _code;
	error["reason"] = _msg;
	root["error"] = error;
	sendJSON(conn, root);	
}


void JSONErrorResponse::setMessage(RESPONSE_ERROR_CODE code, const char* msg) {
	_code = code;
	_msg = msg;
}

} /* namespace Sylvester */