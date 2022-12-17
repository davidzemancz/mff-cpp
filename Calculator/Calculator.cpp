#include <iostream>
#include <string>
#include "Storage.h"
#include "Expr.h"
#include "Stack.h"
#include <stack>
#include "ExprVal.h"

using namespace std;

int main(int argc, char* argv[]) {
	
	Storage storage;

	string strExpr;
	while (cin >> strExpr && strExpr != "")
	{
		string exprName;
		const ExprVal* res = Expr(strExpr, storage).Evaluate();
		cout << *res << endl;
	}

	return 0;
}