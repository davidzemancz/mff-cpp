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
	string colNamesStr;
	string colTypesStr;
	getline(cin, colNamesStr);
	getline(cin, colTypesStr);

	vector<string> colNames = strSplit(colNamesStr, D);
	vector<string> colTypes = strSplit(colTypesStr, D);
	for (size_t i = 0; i < colNames.size(); i++) {

		ColDataType colDt = StrToDataType(colTypes[i]);
		df.addCol(DataFrameCol(i, colNames[i], colDt));
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

	size_t counter = 0;
	size_t colsCount = df.cols.size();
	DataFrameCol* cols = new DataFrameCol[colsCount];
	for (const auto& col : df.cols){
		cols[col.second.m_pos] = col.second;
	}

	for (size_t i = 0; i < colsCount; i++) {
		if (counter > 0) cout << ";";
		cout << cols[i].m_name;
		counter++;
	}

	

	for (const auto& row : df.rows){
		cout << endl;
		counter = 0;
		for (const string& elem : row) {
			if (counter > 0) cout << ";";
			cout << elem;
			counter++;
		}
	}

	delete[] cols;
}

int mainRecodex() {
	string query;
	DataFrame df = readData(query);
	writeData(df.apply(query));

	return 0;
}

int mainLocal()
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

int main()
{
	return mainLocal();
}