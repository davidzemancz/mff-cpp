#include <iostream>
#include <string>
#include "Storage.h"
#include "Expr.h"
#include <stack>

using namespace std;

void printExprVal(const Storage& storage, const TypeEnum& exprType, const string& exprName) {
	switch (exprType) {
	case TypeEnum::Int:
		cout << storage.GetInt(exprName);
		break;
	case TypeEnum::Float:
		cout << storage.GetFloat(exprName);
		break;
	case TypeEnum::Double:
		cout << storage.GetDouble(exprName);
		break;
	};
}

void evalExprs(const Storage& storage) {
	string strExpr;
	while (cin >> strExpr && strExpr != "")
	{
		TypeEnum exprType;
		string exprName;
		Expr(strExpr).Evaluate(storage, exprType, exprName);
		printExprVal(storage, exprType, exprName);
	}
}

class ExprVal {
public:
	virtual ExprVal& Plus(const ExprVal& expr) = 0;
};

class ExprValInt : public ExprVal {

public:
	int val;

	ExprValInt(int val) : val(val) {};

	ExprVal& Plus(const ExprVal& expr) {
		return *this;
	}
};

int main(int argc, char* argv[]) {
	
	ExprValInt e(5);
	stack<ExprVal*> st;
	st.push(&e);
	ExprValInt* ie = dynamic_cast<ExprValInt*>(st.top());
	cout << ie->val;
	
	return 0;

	Storage storage;
	evalExprs(storage);

	return 0;
}