//
//  main.h
//
//  Created by Niels Joubert on 2011-01-21.
//

#include "server.h"

int main(int argc, char *argv[]) {
	
	Sylvester::Server server;
	server.start();
		
	return 0;
}
