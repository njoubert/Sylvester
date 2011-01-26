#include "Sylvester/requesthandler.h"


namespace Sylvester {

RequestHandler::RequestHandler()  : _log(GETLOG("REQUEST_HANDLER")) {
	
}

//todo(njoubert): MAJOR REFACOR:
//  Don't call handleError and then just return, 
//  let handleError and any of the other handleX methods return a Response object.
//  this response will be sent to the client.
//  Think of it as the Option type that can return either an error or a good result.

bool RequestHandler::handle(struct mg_connection *conn, const struct mg_request_info *request_info) {
	_log.log(LOG_INFO, "Mongoose New Request: %s\n", request_info->uri);
		if (strcmp(request_info->uri, "/graph") == 0) {
			//God, Please forgive me for writing this
			if (strcmp(request_info->request_method, "POST") != 0) {
				handleError(conn, ERR_INCORRECT_METHOD_POST, request_info->request_method);		
			} else if (mg_get_header(conn,"Content-Type") == NULL) { //content-type
				handleError(conn, ERR_NO_CONTENT_TYPE, NULL);
			} else if (strcmp(mg_get_header(conn,"Content-Type"), "application/x-javascript") != 0) {
				handleError(conn, ERR_WRONG_CONTENT_TYPE_JAVASCRIPT, mg_get_header(conn,"Content-Type"));					
			} else if (mg_get_header(conn,"Content-Length") == NULL || atoi(mg_get_header(conn,"Content-Length")) == 0) {
				handleError(conn, ERR_NO_CONTENT,NULL);
			} else {
				Json::Value received_json;
				if (getJSONFromRequest(conn, received_json))
					return handleGraphRequest(conn,received_json);
				handleError(conn, ERR_JSON_PARSING, "JSON::Parser returned false");	
				return false;
			}
			
		} else if (strcmp(request_info->uri, "/config") == 0) {
		
		
		
		} else {
			handleError(conn, ERR_UNKNOWN_PATH, request_info->uri);
		}
		return true;	
}

bool RequestHandler::getJSONFromRequest(struct mg_connection *conn, Json::Value& ret) {
	Json::Reader reader;
	
	_log.log(LOG_INFO, "Parsing data from /graph POST request.\n");
	int contentLength = atoi(mg_get_header(conn,"Content-Length"));
	char* contentData = (char*) malloc(sizeof(char)*(contentLength+1));
	
	if (contentData == NULL) {
		_log.log(LOG_ERROR, "Could not malloc bodyData for received request.\n");
		handleError(conn, ERR_MAJOR_SERVER_ERROR, "Could not malloc bodyData for received request.");
		return false;
	}
	
	int contentLengthRead = mg_read(conn, contentData, contentLength);
	
	if (contentLengthRead != contentLength) {
		_log.log(LOG_ERROR, "Did not receive the same amount of data as content length claimed\n");
		handleError(conn, ERR_SERVER_ERROR, "Could not malloc bodyData for received request.");	
		return false;
	}
	contentData[contentLengthRead] = 0;
	_log.log(LOG_INFO, "Received %d bytes successfully.\n", contentLength);
	
	return reader.parse(string(contentData),ret);
}

bool RequestHandler::handleGraphRequest(struct mg_connection *conn, Json::Value& received) {
	if (!verifyGraphRequestJSON(received)) {
		handleError(conn, ERR_MALFORMED_GRAPHREQUEST, NULL);
		return false;
	}
	
	
	
	
	return true;
}
//just confirms that graph->nodes[]/edges[], current->id, new[] exists.
bool RequestHandler::verifyGraphRequestJSON(Json::Value& d) {
	if (!d.isMember("graph"))
		return false;	
	if (!d["graph"].isMember("nodes"))
		return false;
	if (!d["graph"].isMember("edges"))
		return false;	
	if (!d["graph"]["nodes"].isArray())
		return false;
	if (!d["graph"]["edges"].isArray())
		return false;

	if (!d.isMember("current"))
		return false;
	if (!d["current"].isObject())
		return false;
	if (!d["current"].isMember("id"))
		return false;

	if (!d.isMember("new"))
		return false;
	if (!d["new"].isArray())
		return false;
	
	return true;
}

//sends back error info
//problem can be null.
void RequestHandler::handleError(struct mg_connection *conn, RESPONSE_ERROR_CODE code, const char* problem) {
	JSONErrorResponse res;
	res.setMessage(code, problem);
	res.send(conn);
}
	

} /* namespace Sylvester */
