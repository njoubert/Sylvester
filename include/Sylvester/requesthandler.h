//
//  requestHandler.h
//
//  Created by Niels Joubert on 2011-01-21.
//

#ifndef SYLVERSER_REQUEST_HANDLER_H_
#define SYLVERSER_REQUEST_HANDLER_H_

#include <mongoose/mongoose.h>
#include "Sylvester/globals.h"
#include "Sylvester/response.h"

namespace Sylvester {

class RequestHandler {
public:
	RequestHandler();
	bool handle(struct mg_connection *conn, const struct mg_request_info *request_info);
	
private:
	bool getJSONFromRequest(struct mg_connection *conn, Json::Value& ret);
	void handleError(struct mg_connection *conn, RESPONSE_ERROR_CODE code, const char* payload);
	bool handleGraphRequest(struct mg_connection *conn, Json::Value& received);
	bool verifyGraphRequestJSON(Json::Value& d);
	Log& _log;
};
	
} /* namespace Sylvester */


#endif /* SYLVERSER_REQUEST_HANDLER_H_ */