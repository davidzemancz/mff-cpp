#include "Storage.h"
#include <algorithm>

void Storage::SetVal(const string& name, const ExprVal* exprVal)
{
	string str = name;
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	vals[str] = exprVal;
}

void Storage::SetVal(const string_view& name, const ExprVal* exprVal)
{
	string str = string(name);
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	vals[str] = exprVal;
}

const ExprVal* Storage::GetVal(const string& name) const
{
	string str = name;
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	return vals.at(str);
}

const ExprVal* Storage::GetVal(const string_view& name) const
{
	string str = string(name);
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	return vals.at(str);
}

