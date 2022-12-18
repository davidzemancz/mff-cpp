#include <iostream>
#include <string>
#include "Storage.h"
#include "Expr.h"
#include "Stack.h"
#include <stack>
#include "ExprVal.h"
#include <fstream>
#include <filesystem>
#include <utility>
#include <iomanip>
namespace fs = std::filesystem;

using namespace std;


int run() {
	Storage storage;

	string strExpr;
	while (cin >> strExpr && strExpr != "")
	{
		string exprName;
		const ExprVal* res = Expr(strExpr, storage).Evaluate();
		if (res == nullptr) cout << ExprVal::INVALID << endl;
		else cout << *res << endl;
	}

	return 0;
}

int runTest(fs::path& path) {
	// Redirect in/out
	ifstream in(path.string());
	streambuf* cinbuf = cin.rdbuf(); //save old buf
	cin.rdbuf(in.rdbuf()); //redirect cin to in.txt!
	path.replace_extension(fs::path(".res"));
	ofstream out(path);
	streambuf* coutbuf = cout.rdbuf(); //save old buf
	cout.rdbuf(out.rdbuf()); //redirect cout to out.txt!

	// Run
	run();

	// Redirect back
	cin.rdbuf(cinbuf);   //reset to standard input again
	cout.rdbuf(coutbuf); //reset to standard output agai

	return 0;
}

int runTests()
{
	const string testDir = "C:\\Users\\david\\OneDrive\\MFFUK\\3-1\\C++\\mff-cpp\\Calculator";

	// Run tests
	for (const auto& entry : fs::directory_iterator(testDir)) {
		auto path = entry.path();
		auto fn = path.filename();
		if (fn.extension() == ".in" && fn.string().substr(0, 4) == "Test") {
			std::cout << "Running test on " << fn << std::endl;
			runTest(path);
			std::cout << "Test " << fn << " completed" << std::endl;
		}
	}


	return 0;
}


int main(int argc, char* argv[]) {

	run();
	runTests();

	return 0;
}
