#ifndef DEPENDENCY_INJECTOR_H
#define DEPENDENCY_INJECTOR_H

#include <mutex>
#include <vector>
#include <cassert>

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
	template <typename Function> void forEachImpl(Function) const;

	template <typename Function> void implDo(size_t, Function) const;

	template <typename Function> void implDo(Function) const;

private:
	std::vector<T*> m_implementations;
	mutable std::mutex m_implProtector;
};

template <class T> DependencyInjector<T>::DependencyInjector() {}

template <class T> DependencyInjector<T>::~DependencyInjector() {}

template<class T> void DependencyInjector<T>::addImpl(T& impl)
{
	std::unique_lock<std::mutex> lck(m_implProtector);
	m_implementations.push_back(&impl);
}

template<class T> template<typename Function>
void DependencyInjector<T>::forEachImpl(Function f) const
{
	std::unique_lock<std::mutex> lck(m_implProtector);

	for(auto impl : m_implementations)
		f(impl);
}

template <class T> template<typename Function>
void DependencyInjector<T>::implDo(size_t implId, Function f) const
{
	assert(implId < m_implementations.size() && "Implementation id too big");

	std::unique_lock<std::mutex> lck(m_implProtector);
	f(m_implementations[implId]);
}

template <class T> template<typename Function>
void DependencyInjector<T>::implDo(Function f) const
{
	assert(m_implementations.size() == 1 &&
		"There must be one and only one implementation to use this method");

	implDo(0, f);
}

#endif // DEPENDENCYINJECTOR_H
