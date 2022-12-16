#pragma once
#include "Storage.h"
class Expr
{
private:


public:
	string& str;
	Expr(string& strExpr);
	int Evaluate(const Storage& storage, TypeEnum& exprType, string& exprName);
};

