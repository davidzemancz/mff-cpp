#pragma once
#include <string>
#include <map>
#include "ExprVal.h"

using namespace std;


class Storage
{
private:
	map<string, ExprVal*> vals;

public:
	void SetVal(const string& name, ExprVal* exprVal);
	void SetVal(const string_view& name, ExprVal* exprVal);
	ExprVal* GetVal(const string& name) const;
	ExprVal* GetVal(const string_view& name) const;
};

