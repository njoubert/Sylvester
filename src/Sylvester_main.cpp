//
//  main.h
//
//  Created by Niels Joubert on 2011-01-21.
//

#include "globals.h"
#include "server.h"

namespace Sylvester {

void init(int argc, char *argv[]) {
	Log& log = GETLOG("MAIN");
	log.log(LOG_STATUS, "Welcome to Sylvester.\n");
	
	Server &server = Server::Instance();
	server.start();

	int c, pc;
	while (1) {
		printf("> ");
		pc = c = getchar();
		while (c != ' ' && c != '\n') { pc = c; c = getchar(); }
		if (pc == 'q') {
			break;			
		} else  if (pc == 's') {
			printf("No status available.\n");
		} else if (pc == 'h') {
			printf("Commands:\n");
			printf("  \'q\' - quit\n");
			printf("  \'s\' - status\n");

		} else {
			printf("Press \'q'\' to quit, 'h' for help.\n");			
		}
	}
	
}

}

int main(int argc, char *argv[]) {
	Sylvester::init(argc, argv);
	return 0;
}
