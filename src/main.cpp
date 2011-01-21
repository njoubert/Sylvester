//
//  main.h
//
//  Created by Niels Joubert on 2011-01-21.
//

#include "server.h"

int main(int argc, char *argv[]) {
	std::cout << "Welcome to Sylvester." << std::endl;
	
	Sylvester::Server &server = Sylvester::Server::Instance();
	server.start();
	
	getchar();
	return 0;
}
