#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <map>
#include "DataFrame.h"
#include <vector>
#include <cstdbool>
#include "Utils.h"

using namespace std;

const string D = ";";

DataFrame readData(string& query) 
{
	DataFrame df;

	// columns names and data types
	string colNames;
	string colTypes;
	getline(cin, colNames);
	getline(cin, colTypes);

	size_t pos = 0;
	size_t last_n = 0; size_t next_n = 0; size_t last_t = 0; size_t next_t = 0;
	while ((next_n = colNames.find(D, last_n)) != string::npos && (next_t = colTypes.find(D, last_t)) != string::npos) {
		string colName = colNames.substr(last_n, next_n - last_n);
		string colType = colTypes.substr(last_t, next_t - last_t);

		ColDataType colDt = ColDataType::String;
		if (colType == "string") colDt = ColDataType::String;
		else if (colType == "int") colDt = ColDataType::Int;
		else if (colType == "double") colDt = ColDataType::Double;

		df.addCol(DataFrameCol(pos++, colName, colDt));

		last_n = next_n + 1;
		last_t = next_t + 1;
	}

	// number of rows
	size_t rowsCount;
	cin >> rowsCount;

	// rows
	string row;
	for (size_t r = 0; r <= rowsCount; r++) {
		getline(cin, row);
		if (row == "") continue;
		vector<string> rowVctr = strSplit(row, D);
		df.addRowVctr(rowVctr);
	}

	// query
	getline(cin, query);

	return df;
}

void writeData(const DataFrame& df) {
	//df.debugPrint();
}

int main()
{
	const string inFile = "C:\\Users\\david\\OneDrive\\MFFUK\\3-1\\C++\\mff-cpp\\Docs\\test.input";
	const string outFile = "C:\\Users\\david\\OneDrive\\MFFUK\\3-1\\C++\\mff-cpp\\Docs\\test1.output";

	ifstream in(inFile);
	streambuf* cinbuf = cin.rdbuf(); //save old buf
	cin.rdbuf(in.rdbuf()); //redirect cin to in.txt!

	ofstream out(outFile);
	streambuf* coutbuf = cout.rdbuf(); //save old buf
	cout.rdbuf(out.rdbuf()); //redirect cout to out.txt!

	string query;
	DataFrame df = readData(query);
	writeData(df.apply(query));

	cin.rdbuf(cinbuf);   //reset to standard input again
	cout.rdbuf(coutbuf); //reset to standard output agai

	return 0;
}
