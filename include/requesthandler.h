//
//  requestHandler.h
//
//  Created by Niels Joubert on 2011-01-21.
//

#ifndef SYLVERSER_REQUEST_HANDLER_H_
#define SYLVERSER_REQUEST_HANDLER_H_

#include <mongoose/mongoose.h>
#include "globals.h"
#include "response.h"

namespace Sylvester {

class RequestHandler {
public:
	RequestHandler();
	void handle(struct mg_connection *conn, const struct mg_request_info *request_info);
	
private:
	// handleGraphRequest();
	// handleSettingsRequest();
	void handleError(struct mg_connection *conn, ERROR_RESPONSE_CODE code, const char* msg);
	Log& _log;
};
	
} /* namespace Sylvester */


#endif /* SYLVERSER_REQUEST_HANDLER_H_ */