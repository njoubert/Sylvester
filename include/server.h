//
//  server.h
//
//  Created by Niels Joubert on 2011-01-21.
//

#ifndef SYLVERSER_SERVER_H_
#define SYLVERSER_SERVER_H_

#include <mongoose/mongoose.h>
#include <cstdio>
#include "globals.h"

namespace Sylvester {

class Server {
public:
	//using Meyers singleton pattern
	static Server& Instance() {
		static Server theSingleton;
		return theSingleton;
	}
	
	void start();
private:
	struct mg_context *ctx;


	//singleton
	Server();
	Server(Server const&);
	Server& operator=(Server const&);
	~Server();
};
	
}


#endif /* SYLVERSER_SERVER_H_ */