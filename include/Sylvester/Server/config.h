//
//  config.h
//
//  Created by Niels Joubert on 2011-01-21.
//
#ifndef SYLVERSER_CONFIG_H_
#define SYLVERSER_CONFIG_H_


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

#endif /* SYLVERSER_CONFIG_H_ */
