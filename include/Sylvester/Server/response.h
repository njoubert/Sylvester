//
//  request.h
//
//  Created by Niels Joubert on 2011-01-21.
//  Copyright (c) 2011 Niels Joubert. All rights reserved.
//
#ifndef INCLUDE_SYLVESTER_SERVER_RESPONSE_H_
#define INCLUDE_SYLVESTER_SERVER_RESPONSE_H_

#include <mongoose/mongoose.h>
#include "json/json.h"

#include "Sylvester/Server/globals.h"

namespace Sylvester {
namespace Server {
	
using ::Json::Value;
using ::Json::Reader;
using ::Json::Writer;

enum RESPONSE_ERROR_CODE {
	ERR_MAJOR_SERVER_ERROR,
	ERR_SERVER_ERROR,
	ERR_INCORRECT_METHOD_POST,
	ERR_UNKNOWN_PATH,
	ERR_NO_CONTENT_TYPE,
	ERR_WRONG_CONTENT_TYPE_JAVASCRIPT,
	ERR_NO_CONTENT,
	ERR_JSON_PARSING,
	ERR_MALFORMED_GRAPHREQUEST
};
static const char* RESPONSE_ERROR_MSG[] = {
	"Major server error. You get to punch Niels. Not too hard though, please, he still needs to fix it...",
	"Error! See payload",
	"Expected but did not receive POST",
	"Requested an unknown path",
	"No Content-Type present",
	"Wrong Content-Type present, expects application/x-javascript",
	"No Content present",
	"Could not parse JSON",
	"/graph was given a malformed graph that did not conform to specification"
};

class Response {
public:
	Response();
protected:
	//Adds necessary headers (including content-length) and sends response to conn.
	void sendHTTPResponse(struct mg_connection *conn, const char* str, size_t len);	
	Log& _log;
};

class JSONResponse : public Response {
public:
	//Abstract method for sending a response. Must be implemented in children
	virtual void send(struct mg_connection *conn)=0;
	
protected:
	//Converts JSON to actual char* request, calls sendHTTPResponse
	void sendJSON(struct mg_connection *conn, const Value& value);
};

class JSONErrorResponse : public JSONResponse {
public:
	void setMessage(RESPONSE_ERROR_CODE code, const char* problem);
	virtual void send(struct mg_connection *conn);
private:
	const char* _msg;
	const char* _problem;
	RESPONSE_ERROR_CODE _code;
};

} /* namespace Server */
} /* namespace Sylvester */

#endif  // INCLUDE_SYLVESTER_SERVER_RESPONSE_H_
