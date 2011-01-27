//
//  config.h
//
//  Created by Niels Joubert on 2011-01-21.
//  Copyright (c) 2011 Niels Joubert. All rights reserved.
//
#ifndef INCLUDE_SYLVESTER_SERVER_CONFIG_H_
#define INCLUDE_SYLVESTER_SERVER_CONFIG_H_


namespace Sylvester {
namespace Server {
		
struct Config {
	bool makeDaemon;
	Config() {
		makeDaemon = false;
	}
};

} /* namespace Server */
} /* namespace Sylvester */

#endif  // INCLUDE_SYLVESTER_SERVER_CONFIG_H_
