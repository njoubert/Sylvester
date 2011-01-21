//
//  request.h
//
//  Created by Niels Joubert on 2011-01-21.
//
#ifndef SYLVERSER_RESPONSE_H_
#define SYLVERSER_RESPONSE_H_

#include <mongoose/mongoose.h>
#include "globals.h"

namespace Sylvester {
enum ERROR_RESPONSE_CODE {
	ERR_INCORRECT_METHOD
};

class JSONResponse {
public:
	virtual void send(struct mg_connection *conn)=0;
};

class JSONErrorResponse : public JSONResponse {
public:
	void setMessage(ERROR_RESPONSE_CODE code, const char* msg);
	virtual void send(struct mg_connection *conn);
private:
	const char* _msg;
	ERROR_RESPONSE_CODE _code;
};

}

#endif /* SYLVERSER_RESPONSE_H_ */
