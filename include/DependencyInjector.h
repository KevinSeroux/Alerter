#ifndef DEPENDENCY_INJECTOR_H
#define DEPENDENCY_INJECTOR_H

#include <mutex>
#include <vector>

// 
// T is the interface class for the different implementations
template <class T> class DependencyInjector
{
public:
	/* Function to add an implementation. Make sure that the referenced
	 * implementation is not destroyed */
	void addImpl(T&);
	
protected:
    DependencyInjector();
    virtual ~DependencyInjector() = 0;

	/* Call this method with a lambda function to iterate over the
	 * implementations */
    template <typename Function> void forEach(Function);

private:
    std::vector<T*> m_implementations;
    std::mutex m_implProtector;
};

template <class T> DependencyInjector<T>::DependencyInjector() {}

template <class T> DependencyInjector<T>::~DependencyInjector() {}

template<class T> void DependencyInjector<T>::addImpl(T& impl)
{
	m_implProtector.lock();
	m_implementations.push_back(&impl);
	m_implProtector.unlock();
}

template<class T> template<typename Function>
void DependencyInjector<T>::forEach(Function f)
{
	m_implProtector.lock();

	for(auto& impl : m_implementations)
	{
		f(impl);
	}

	m_implProtector.unlock();
}

#endif // DEPENDENCYINJECTOR_H
