//
//  requestHandler.h
//
//  Created by Niels Joubert on 2011-01-21.
//  Copyright (c) 2011 Niels Joubert. All rights reserved.
//

#ifndef INCLUDE_SYLVESTER_SERVER_REQUESTHANDLER_H_
#define INCLUDE_SYLVESTER_SERVER_REQUESTHANDLER_H_

#include <mongoose/mongoose.h>
#include "Sylvester/Server/globals.h"
#include "Sylvester/Server/response.h"

namespace Sylvester {
namespace Server {

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

} /* namespace Server */
} /* namespace Sylvester */


#endif  // INCLUDE_SYLVESTER_SERVER_REQUESTHANDLER_H_