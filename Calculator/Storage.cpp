#include "Storage.h"
#include <algorithm>

void Storage::SetVal(const string& name, ExprVal* exprVal)
{
	string str = name;
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	vals[str] = exprVal;
}

void Storage::SetVal(const string_view& name, ExprVal* exprVal)
{
	string str = string(name);
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	vals[str] = exprVal;
}

ExprVal* Storage::GetVal(const string& name) const
{
	string str = name;
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	return vals.at(str);
}

ExprVal* Storage::GetVal(const string_view& name) const
{
	string str = string(name);
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	return vals.at(str);
}

