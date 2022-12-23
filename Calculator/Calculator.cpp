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
	while (getline(cin, strExpr) && strExpr != "")
	{
		if (strExpr[0] == '#') continue; // Skip comments

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


bool filesAreSame(fs::path& path) {
	path.replace_extension(fs::path(".out"));
	const string p1 = path.string();
	path.replace_extension(fs::path(".res"));
	const string p2 = path.string();

	std::ifstream f1(p1, std::ifstream::binary | std::ifstream::ate);
	std::ifstream f2(p2, std::ifstream::binary | std::ifstream::ate);

	if (f1.fail() || f2.fail()) {
		return false; //file problem
	}

	if (f1.tellg() != f2.tellg()) {
		return false; //size mismatch
	}

	//seek back to beginning and use std::equal to compare contents
	f1.seekg(0, std::ifstream::beg);
	f2.seekg(0, std::ifstream::beg);
	return std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
		std::istreambuf_iterator<char>(),
		std::istreambuf_iterator<char>(f2.rdbuf()));
}

int runTests()
{
	const string testDir = "C:\\Users\\david\\OneDrive\\MFFUK\\3-1\\C++\\mff-cpp\\Calculator";

	// Run tests
	for (const auto& entry : fs::directory_iterator(testDir)) {
		auto path = entry.path();
		auto fn = path.filename();
		if (fn.extension() == ".in" && fn.string().substr(0, 4) == "Test") {
			ifstream inFile(path);
			string commentLine;
			getline(inFile, commentLine);

			runTest(path);
			
			string status = filesAreSame(path) ? "  OK  " : "failed";

			std::cout << fn << " | " << status << " | " << commentLine.substr(2)  << std::endl;
		}
	}

	return 0;
}


int main(int argc, char* argv[]) {

	//run();
	runTests();

	return 0;
}
