//
//  config.h
//
//  Created by Niels Joubert on 2011-01-21.
//
#ifndef SYLVERSER_CONFIG_H_
#define SYLVERSER_CONFIG_H_


namespace Sylvester {

struct Config {
	bool makeDaemon;
	Config() {
		makeDaemon = false;
	}
};

}

#endif /* SYLVERSER_CONFIG_H_ */
