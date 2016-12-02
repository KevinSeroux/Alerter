#ifndef SINGLETON__H
#define SINGLETON__H

template <class T> class Singleton
{
public:
	static T& getInstance();

protected:
	Singleton();
};

template <class T> Singleton<T>::Singleton() {}

template <class T> T& Singleton<T>::getInstance()
{
	// In C++11 the initialization is made by only one thread, the others wait
	static T instance;
	return instance;
}

#endif // SINGLETON__H
