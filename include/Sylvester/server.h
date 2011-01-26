//
//  server.h
//
//  Created by Niels Joubert on 2011-01-21.
//

#ifndef SYLVERSER_SERVER_H_
#define SYLVERSER_SERVER_H_

#include <mongoose/mongoose.h>
#include "Sylvester/globals.h"
#include "Sylvester/requestHandler.h"

namespace Sylvester {

class Server {
public:
	//using Meyers singleton pattern
	static Server& Instance() {
		static Server theSingleton;
		return theSingleton;
	}
	
	void start();
	int handleRequest(enum mg_event event,
                           struct mg_connection *conn,
                           const struct mg_request_info *request_info);
private:
	struct mg_context *ctx;
	Log& _log;
	RequestHandler _requestHandler;
	void printRequestInfo(const struct mg_request_info *request_info);
	
	//singleton
	Server();
	Server(Server const&);
	Server& operator=(Server const&);
	~Server();
};
	
} /* namespace Sylvester */


#endif /* SYLVERSER_SERVER_H_ */