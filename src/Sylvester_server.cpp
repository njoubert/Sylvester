#include "server.h"



namespace Sylvester {

//extern "C" {
static void *event_handler(enum mg_event event,
                           struct mg_connection *conn,
                           const struct mg_request_info *request_info) {
	//void *processed = const_cast<char *>("yes");
	
	Server &server = Server::Instance();
	server.handleRequest(event, conn, request_info);
	
 	return (void*)1;
}

static const char *options[] = {
  "document_root", "html",
  "listening_ports", "8083",
  "num_threads", "5",
  NULL
};
//}

Server::Server() : _log(GETLOG("SERVER")) {
	ctx = NULL;
}

Server::~Server() {
	if (ctx != NULL) {
		_log.log(LOG_INFO, "Stopping mongoose server...\n");
		mg_stop(ctx);
	}
	
}

void Server::start() {
	ctx = mg_start(&event_handler, options);
	if (ctx == NULL)
		throw 42;

	_log.log(LOG_INFO,"Chat server started on ports %s, press enter to quit.\n", mg_get_option(ctx, "listening_ports"));
}	

void Server::handleRequest(enum mg_event event,
                          struct mg_connection *conn,
                          const struct mg_request_info *request_info) {

	_log.log(LOG_INFO,"Request arrived.\n");
	
}

} /* namespace Sylvester */
