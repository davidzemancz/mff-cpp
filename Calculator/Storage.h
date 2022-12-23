#pragma once
#include <string>
#include <map>
#include "ExprVal.h"

using namespace std;


class Storage
{
private:
	map<string, const ExprVal*> vals;

public:
	void SetVal(const string& name, const ExprVal* exprVal);
	void SetVal(const string_view& name, const ExprVal* exprVal);
	const ExprVal* GetVal(const string& name) const;
	const ExprVal* GetVal(const string_view& name) const;
};

