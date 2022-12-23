#pragma once
#include "Storage.h"
class Expr
{
private:
	ExprVal* evaluate(const string_view& tokens) const ;

public:
	const string& str;
	Storage& storage;

	Expr(const string& strExpr, Storage& storage);
	const ExprVal* Evaluate() const;
};

