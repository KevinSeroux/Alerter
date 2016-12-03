#include "OptionTypedData.h"

OptionTypedData::OptionTypedData()
{

}

OptionTypedData::OptionTypedData(const OptionTypedData& optionTypedData)
{
	// That's all! The std::mutex should not be copied
	m_value = optionTypedData.m_value;
}

OptionTypedData& OptionTypedData::operator=(const char p_value[])
{
	std::string value(p_value);
	return operator=(value);
}

bool OptionTypedData::operator==(const char p_value[]) const
{
	std::string value(p_value);
	return operator==(value);
}
