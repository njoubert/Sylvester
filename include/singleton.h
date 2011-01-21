
// singleton.h
#ifndef _SINGLETON_H_
#define _SINGLETON_H_

namespace Sylvester {

template <class T>
class Singleton {
public:
	static T& Instance() {
		static T _instance;
		return _instance;
	}
private:
  Singleton();
  ~Singleton();
  Singleton(Singleton const&);
  Singleton& operator=(Singleton const&);
};

}

#endif /* _SINGLETON_H_ */
