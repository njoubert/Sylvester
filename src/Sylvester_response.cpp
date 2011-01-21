#include "response.h"
#include <sstream>

namespace Sylvester {

static const char *ajax_reply_start =
	"HTTP/1.1 200 OK\r\n"
	"Cache: no-cache\r\n"
	"Content-Type: application/x-javascript\r\n";

void JSONErrorResponse::send(struct mg_connection *conn) {
	char b[2048];
	sprintf(b, "{\n \"error\": \"%s\",\n \"code\":%d\n}\n", _msg, _code);
	int len = strlen(b);
	mg_printf(conn, "%sContent-Length:%d\r\n\r\n", ajax_reply_start, len);
	mg_printf(conn, b);
}


void JSONErrorResponse::setMessage(ERROR_RESPONSE_CODE code, const char* msg) {
	_code = code;
	_msg = msg;
}



} /* namespace Sylvester */
