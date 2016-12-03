#ifndef OPTION_TYPED_DATA__H
#define OPTION_TYPED_DATA__H

#include <boost/variant.hpp>
#include <mutex>
#include <string>

class OptionTypedData
{
public:
	OptionTypedData();
	OptionTypedData(const OptionTypedData&);

	OptionTypedData& operator=(const char[]);
	template <class T> OptionTypedData& operator=(T&);

	bool operator==(const char[]) const;
	template <class T> bool operator==(T&) const;

	template <class T> bool operator!=(T&) const;

private:
	boost::variant<std::string, bool> m_value;
	mutable std::mutex m_valueProtector; // Mutable to use "const"
};

template <class T> OptionTypedData& OptionTypedData::operator=(T& p_value)
{
	boost::variant<T> value(p_value);

	m_valueProtector.lock();
	m_value = p_value;
	m_valueProtector.unlock();

	return *this;
}

template <class T> bool OptionTypedData::operator==(T& val) const
{
	// Use a mutex to ensure having the latest value
	m_valueProtector.lock();
	bool retValue = (boost::get<T>(m_value) == val);
	m_valueProtector.unlock();

	return retValue;
}

template <class T> inline bool OptionTypedData::operator!=(T& val) const
{
	return !operator==(val);
}

#endif //OPTION_INT__H
