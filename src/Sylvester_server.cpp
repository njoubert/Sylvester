#include "server.h"


namespace Sylvester {

static void *event_handler(enum mg_event event,
                           struct mg_connection *conn,
                           const struct mg_request_info *request_info) {
	//void *processed = const_cast<char *>("yes");
	
	Server &server = Server::Instance();
	return (void*) server.handleRequest(event, conn, request_info);
}

static const char *options[] = {
  "document_root", "html",
  "listening_ports", "8083",
  "num_threads", "5",
  NULL
};

Server::Server() : _log(GETLOG("SERVER")), _requestHandler() {
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

// handle the request, return 0 if everything is OK.
int Server::handleRequest(enum mg_event event,
                          struct mg_connection *conn,
                          const struct mg_request_info *request_info) {

	int processed = 0;
	switch (event) {
			case MG_NEW_REQUEST:    // New HTTP request has arrived from the client
				_requestHandler.handle(conn, request_info);
				processed = 1;
				break;
			case MG_HTTP_ERROR :    // HTTP error must be returned to the client
				_log.log(LOG_WARN, "Mongoose HTTP error.\n");
				break;
			case MG_EVENT_LOG  :    // Mongoose logs an event, request_info.log_message
				_log.log(LOG_WARN, "Mongoose Event Logged.\n");
				break;
			case MG_INIT_SSL   :    // Mongoose initializes SSL. Instead of mg_connection *,
				_log.log(LOG_WARN, "SSL Not Supported.\n");
				break;
	}
	return processed;
}

} /* namespace Sylvester */
