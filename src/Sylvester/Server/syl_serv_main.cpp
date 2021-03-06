//
//  main.h
//
//  Created by Niels Joubert on 2011-01-21.
//

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "Sylvester/Server/globals.h"
#include "Sylvester/Server/server.h"
#include "Sylvester/Server/config.h"

namespace Sylvester {
namespace Server {

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

static void daemonize(void) {
	pid_t pid, sid;
	
	/* already a daemon */
	if ( getppid() == 1 ) return;
	printf("Daemonizing...\n");
	/* Fork off the parent process */
	pid = fork();
	if (pid < 0) {
		exit(EXIT_FAILURE);
	}
	/* If we got a good PID, then we can exit the parent process. */
	if (pid > 0) {
		exit(EXIT_SUCCESS);
	}
	
	/* At this point we are executing as the child process */
	
	/* Change the file mode mask */
	umask(0);
	
	/* Create a new SID for the child process */
	sid = setsid();
	if (sid < 0) {
		exit(EXIT_FAILURE);
	}
	
	/* Change the current working directory.  This prevents the current
	   directory from being locked; hence not being able to remove it. */
	if ((chdir("/")) < 0) {
		exit(EXIT_FAILURE);
	}
	
	/* Redirect standard files to /dev/null */
	freopen( "/dev/null", "r", stdin);
	freopen( "/dev/null", "w", stdout);
	freopen( "/dev/null", "w", stderr);
}

int getWord(char* buffer) {
	int count = 0;
	int c;
	while ((c = getchar()) != ' ' && c != '\n') { buffer[count] = c; count++; }
	return count;
}

void init(Config *config) {
	Log& log = GETLOG("MAIN");
	log.log(LOG_STATUS, "Welcome to Sylvester.\n");

	if (config->makeDaemon)
		daemonize();
		
	Server &server = Sylvester::Server::Server::Instance();
	server.start();
	
	char buffer[1024];
	int c;
	while (1) {
		printf("> ");
		c = getWord(buffer);
		if (buffer[0] == 'q') {
			break;			
		} else  if (buffer[0] == 's') {
			printf("No status available.\n");
		} else  if (buffer[0] == 'l') {
			c = getWord(buffer);
			if (c == 1 && buffer[0] > 47 && buffer[0] < 56) {
				Singleton<LogFactory>::Instance().setAllLogLevel((LOGLEVEL)(buffer[0]-48));
			} else {
				printf("Specify a logging level 0-7 (0 is off).\n");
			}
		} else if (buffer[0] == 'h') {
			printf("Commands:\n");
			printf("  \'q\' - quit\n");
			printf("  \'s\' - status\n");
			printf("  \'l [0-6]\' - change logging level\n");
		} else {
			printf("Press \'q'\' to quit, 'h' for help.\n");			
		}			
	}
	
}

} /* namespace Server */
} /* namespace Sylvester */

void usage() {
	printf("usage: sylvester [--daemon]\n");
	printf("  --daemon        Forks the service as a daemon.\n");
}

int main(int argc, char *argv[]) {
	Sylvester::Server::Config config;
	
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i],"--daemon") == 0) {
			config.makeDaemon = true;
		} else {
			fprintf(stderr,"Option not recognized, quitting %s\n", argv[i]);
			usage();
			exit(1);
		}
	}
	
	Sylvester::Server::init(&config);
	return 0;
}
