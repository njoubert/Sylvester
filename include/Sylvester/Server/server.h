//
//  server.h
//
//  Created by Niels Joubert on 2011-01-21.
//  Copyright (c) 2011 Niels Joubert. All rights reserved.
//

#ifndef INCLUDE_SYLVESTER_SERVER_SERVER_H_
#define INCLUDE_SYLVESTER_SERVER_SERVER_H_

#include <mongoose/mongoose.h>

#include "Sylvester/Server/globals.h"
#include "Sylvester/Server/requesthandler.h"

namespace Sylvester {
namespace Server {

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
	explicit Server(Server const&);
	Server& operator=(Server const&);
	~Server();
};

} /* namespace Server */
} /* namespace Sylvester */


#endif  // INCLUDE_SYLVESTER_SERVER_SERVER_H_