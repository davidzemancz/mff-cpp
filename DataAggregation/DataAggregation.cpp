#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <tuple>
#include <map>
#include <unordered_map>
#include <vector>
#include <vector>
#include <cstdbool>
#include <iostream>
#include <sstream>

using namespace std;

enum class ColDataType { Unknown = 0, Int = 1, String = 2, Double = 3 };
enum class ColAggFun { None = 0, Sum = 1, Min = 2, Max = 3 };

class Col
{
public:
	size_t m_pos;
	string m_name;
	ColDataType m_dataType;
	ColAggFun m_aggFun;

	Col() {}
	Col(const size_t pos, const string& name) : m_pos(pos), m_name(name) {}
	Col(const size_t pos, const string& name, const ColDataType dataType) : m_pos(pos), m_name(name), m_dataType(dataType) {}
	Col(const size_t pos, const string& name, const ColDataType dataType, const ColAggFun aggFun) : m_pos(pos), m_name(name), m_dataType(dataType), m_aggFun(aggFun) {}
};

const string D = ";";
vector<Col> cols;
vector<vector<string>> rows;
string query;

ColDataType strToDataType(string& str) {
	if (strcmp(str.c_str(), "string") == 0) return ColDataType::String;
	else if (strcmp(str.c_str(), "int") == 0) return ColDataType::Int;
	else if (strcmp(str.c_str(), "double") == 0) return ColDataType::Double;
	return ColDataType::Unknown;
}

ColAggFun strToAggFun(string& str) {
	if (strcmp(str.c_str(), "SUM") == 0) return ColAggFun::Sum;
	else if (strcmp(str.c_str(), "MIN") == 0) return ColAggFun::Min;
	else if (strcmp(str.c_str(), "MAX") == 0) return ColAggFun::Max;
	return ColAggFun::None;
}

void readData() 
{
	// Column names
	string str;
	string colNames;
	cin >> colNames;
	stringstream ssNames(colNames);
	size_t colIndex = 0;
	while (getline(ssNames, str, ';')) {
		if (str == "") break;
		Col col = Col(colIndex++, str);
		cols.push_back(col);
	}

	// Column data types
	string colTypes;
	cin >> colTypes;
	stringstream ssTypes(colTypes);
	colIndex = 0;
	while (getline(ssTypes, str, ';')) {
		if (str == "") break;
		cols[colIndex].m_dataType = strToDataType(str);
	}

	// Number of rows
	size_t rowsCount;
	cin >> rowsCount;

	// rows
	rows.reserve(rowsCount);
	string row;
	for (size_t r = 0; r < rowsCount; r++) {
		getline(cin, row);
		if (row == "") { r--; continue; }
		rows.push_back(vector<string>());
		rows[r].reserve(cols.size());
		stringstream ssRow(row);
		while (getline(ssRow, str, ';')) {
			rows[r].push_back(str);
		}
	}

	// query
	getline(cin, query);
}

void printAgg() {
	string groupBy;
	vector<string> selects;
	unordered_map<string, Col> aggCols;
	unordered_map<string, Col> colsMap;

	for (Col& col : cols) {
		colsMap[col.m_name] = col;
	}

	// SELECT prijmeni, SUM(jmeno), MIN(key), MAX(key), MIN(vek), MAX(vek), SUM(deti), SUM(rodice), MIN(prumer), MAX(prumer) GROUP_BY prijmeni

	// Consts
	const string SELECT = "SELECT";
	const string GROUP_BY = "GROUP_BY";

	// Process query
	stringstream ss(query);
	string word;
	size_t count = 0;
	while (ss >> word) {
		if (word == "") continue;
		if (word == SELECT) continue;

		if (word.back() == ',') {
			word.pop_back();
		}

		if (word == GROUP_BY) {
			ss >> groupBy;
		}
		else {
			string aggFunStr = word.substr(0, 3);
			ColAggFun aggFun = strToAggFun(aggFunStr);
			string colName = aggFun == ColAggFun::None ? word : word.substr(4, word.size() - 5);
			aggCols[word] = Col(count++, colName, colsMap.at(colName).m_dataType, aggFun);
			selects.push_back(word);
		}
	}

	// Groups
	/*size_t groupByIndex = colsMap.at(groupBy).m_pos;
	map<string, vector<size_t>> groups;
	for (size_t r = 0; r < rows.size(); r++) {
		groups[rows[r][groupByIndex]].push_back(r);
	}*/


	//// Print cols
	//size_t colCounter = 0;
	//for (const string& select : selects) {
	//	if (colCounter > 0) cout << ";";
	//	cout << select;
	//	colCounter++;
	//}

	//// Aggregate rows
	//for (const auto& group : groups) {
	//	colCounter = 0;
	//	cout << endl;
	//	for (const string& select : selects) {
	//		Col col = aggCols.at(select);
	//		size_t colIndex = cols.at(col.m_tag).m_pos;
	//		ColDataType colDt = col.m_dataType;
	//		size_t rowCounter = 0;
	//		if (colDt == ColDataType::String) {
	//			string value;
	//			for (const size_t r : group.second) {
	//				if (rowCounter == 0) value = rows[r][colIndex];
	//				else if (col.m_aggFun == ColAggFun::Sum) value += rows[r][colIndex];
	//				else value = rows[r][colIndex];
	//				rowCounter++;
	//			}

	//			// Print
	//			if (colCounter > 0) cout << ";";
	//			cout << value;
	//			colCounter++;
	//		}
	//		else if (colDt == ColDataType::Int) {
	//			int value = 0;
	//			for (const size_t r : group.second) {
	//				if (rowCounter == 0) value = stoi(rows[r][colIndex]);
	//				else if (col.m_aggFun == ColAggFun::Sum) value += stoi(rows[r][colIndex]);
	//				else if (col.m_aggFun == ColAggFun::Min) value = min(stoi(rows[r][colIndex]), value);
	//				else if (col.m_aggFun == ColAggFun::Max) value = max(stoi(rows[r][colIndex]), value);
	//				rowCounter++;
	//			}

	//			// Print
	//			if (colCounter > 0) cout << ";";
	//			cout << to_string(value);
	//			colCounter++;
	//		}
	//		else if (colDt == ColDataType::Double) {
	//			double value = 0.0;
	//			for (const size_t r : group.second) {
	//				if (rowCounter == 0) value = stod(rows[r][colIndex]);
	//				else if (col.m_aggFun == ColAggFun::Sum) value += stod(rows[r][colIndex]);
	//				else if (col.m_aggFun == ColAggFun::Min) value = min(stod(rows[r][colIndex]), value);
	//				else if (col.m_aggFun == ColAggFun::Max) value = max(stod(rows[r][colIndex]), value);
	//				rowCounter++;
	//			}

	//			// Print
	//			if (colCounter > 0) cout << ";";
	//			cout << to_string(value);
	//			colCounter++;
	//		}
	//	}
	//}
}

int mainRecodex() {
	readData();
	printAgg();
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

	readData();
	printAgg();

	cin.rdbuf(cinbuf);   //reset to standard input again
	cout.rdbuf(coutbuf); //reset to standard output agai

	return 0;
}

int main()
{
	return mainRecodex();
}