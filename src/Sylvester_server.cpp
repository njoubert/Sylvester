
#include "server.h"


//extern "C" {
static void *event_handler(enum mg_event event,
                           struct mg_connection *conn,
                           const struct mg_request_info *request_info) {
	//void *processed = const_cast<char *>("yes");
	
	printf("Request Received\n");
 	return NULL;
}

static const char *options[] = {
  "document_root", "html",
  "listening_ports", "8083",
  "num_threads", "5",
  NULL
};
//}

namespace Sylvester {

Server::Server() {
	
}

Server::~Server() {
	
}

void Server::start() {
	std::cout << "SERVER STARTING" << std::endl;
	struct mg_context *ctx = NULL;
	ctx = mg_start(&event_handler, options);
	if (ctx == NULL)
		throw 42;

	  printf("Chat server started on ports %s, press enter to quit.\n", mg_get_option(ctx, "listening_ports"));
}	

}
