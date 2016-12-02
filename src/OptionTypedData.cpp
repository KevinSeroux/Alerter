#include "OptionTypedData.h"

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
