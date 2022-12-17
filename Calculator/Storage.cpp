#include "Storage.h"

void Storage::SetVal(const string& name, const ExprVal* exprVal)
{
	vals[name] = exprVal;
}

const ExprVal* Storage::GetVal(const string& name) const
{
	return vals.at(name);
}

const ExprVal* Storage::GetVal(const string_view& name) const
{
	return vals.at(string(name));
}

