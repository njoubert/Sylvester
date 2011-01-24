//
//  request.h
//
//  Created by Niels Joubert on 2011-01-21.
//
#ifndef SYLVERSER_RESPONSE_H_
#define SYLVERSER_RESPONSE_H_

#include <mongoose/mongoose.h>
#include "globals.h"
#include "json/json.h"

namespace Sylvester {
	
using namespace ::Json;

enum RESPONSE_ERROR_CODE {
	ERR_INCORRECT_METHOD,
	ERR_UNKNOWN_PATH
};

class Response {
	
protected:
	//Adds necessary headers (including content-length) and sends response to conn.
	void sendHTTPResponse(struct mg_connection *conn, const char* str, size_t len);	
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
	void setMessage(RESPONSE_ERROR_CODE code, const char* msg);
	virtual void send(struct mg_connection *conn);
private:
	const char* _msg;
	RESPONSE_ERROR_CODE _code;
};

}

#endif /* SYLVERSER_RESPONSE_H_ */
