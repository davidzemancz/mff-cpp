#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <tuple>
#include <map>
#include <unordered_map>
#include <vector>
#include <vector>
#include <iostream>
#include <sstream>
#include <string_view>
#include <charconv>

using namespace std;

enum class ColAggFun { None = 0, Sum = 1, Min = 2, Max = 3 };
enum class ColDataType { Unknown = 0, String = 1, Int = 2, Double = 3 };

class Col
{
public:
	size_t m_pos;
	string m_name;
	ColDataType m_dataType;

	Col() {}
	Col(const size_t pos, const string& name, const ColDataType dataType) : m_pos(pos), m_name(name), m_dataType(dataType) {}
	virtual ~Col() {}
};


class AggCol
{
public:
	string m_name;
	Col* m_origCol;
	ColAggFun m_aggFun;

	AggCol() {}
	AggCol(const string& name, Col* origCol, const ColAggFun aggFun) : m_name(name), m_origCol(origCol), m_aggFun(aggFun) {}
	virtual ~AggCol() {}
};

class IntCol : public Col
{
public:
	vector<int> vals;

	IntCol() {}
	IntCol(const size_t pos, const string& name, const ColDataType dataType, const size_t size) : Col(pos, name, dataType){ vals.reserve(size); }
	~IntCol() {}
};

class DoubleCol : public Col
{
public:
	vector<double> vals;

	DoubleCol() {}
	DoubleCol(const size_t pos, const string& name, const ColDataType dataType, const size_t size) : Col(pos, name, dataType) { vals.reserve(size); }
	~DoubleCol() {}
};

class StringCol : public Col
{
public:
	vector<string> vals;

	StringCol() {}
	StringCol(const size_t pos, const string& name, const ColDataType dataType, const size_t size) : Col(pos, name, dataType) { vals.reserve(size); }
	~StringCol() {}
};

const char D = ';';
vector<Col*> cols;

ColDataType strToDataType(string_view str) {
	if (str == "string") return ColDataType::String;
	else if (str == "int") return ColDataType::Int;
	else if (str == "double") return ColDataType::Double;
	return ColDataType::Unknown;
}
ColAggFun strToAggFun(string_view str) {
	if (str == "SUM") return ColAggFun::Sum;
	else if (str == "MIN") return ColAggFun::Min;
	else if (str == "MAX") return ColAggFun::Max;
	return ColAggFun::None;
}

Col* getCol(string& name) {
	for (Col* col : cols) {
		if (col->m_name == name) return col;
	}
	return nullptr;
}

vector<string_view> splitString(string& str, char sep) {
	vector<string_view> r;
	const char* f = str.c_str();
	size_t s = 0;
	for(const char* i = f;;i++)
	{
		if (*i == 0  || *i == sep) {
			r.emplace_back(f, s);
			if (*i == 0) break;
			f = ++i;
			s = 0;
		}
		s++;
	}
	return r;
}

void readData() 
{

	// Cols
	string colNamesStr, colTypesStr;
	cin >> colNamesStr;
	vector<string_view> colNames = splitString(colNamesStr, D);
	cin >> colTypesStr;
	vector<string_view> colTypes = splitString(colTypesStr, D);
	size_t rowsCount;
	cin >> rowsCount;
	size_t colIndex = 0;
	for (size_t i = 0; i < colNames.size(); i++) {
		if (colTypes[i] == "int") cols.push_back(new IntCol(colIndex++, string(colNames[i]), strToDataType(colTypes[i]), rowsCount));
		else if (colTypes[i] == "double") cols.push_back(new DoubleCol(colIndex++, string(colNames[i]), strToDataType(colTypes[i]), rowsCount));
		else if (colTypes[i] == "string") cols.push_back(new StringCol(colIndex++, string(colNames[i]), strToDataType(colTypes[i]), rowsCount));
	}

	// Rows
	string row = "";
	for (size_t r = 0; r < rowsCount; r++) {
		cin >> row;

		vector<string_view> cells = splitString(row, D);

		colIndex = 0;
		for (size_t i = 0; i < cells.size(); i++) {
			if (cols[colIndex]->m_dataType == ColDataType::String) {
				StringCol* sCol = dynamic_cast<StringCol*>(cols[colIndex]);
				sCol->vals.emplace_back(cells[i]);
			}
			else if (cols[colIndex]->m_dataType == ColDataType::Int) {
				IntCol* sCol = dynamic_cast<IntCol*>(cols[colIndex]);
				int integer;
				from_chars(cells[i].data(), cells[i].data() + cells[i].size(), integer);
				sCol->vals.push_back(integer);
			}
			else if (cols[colIndex]->m_dataType == ColDataType::Double) {
				DoubleCol* sCol = dynamic_cast<DoubleCol*>(cols[colIndex]);
				double doub;
				from_chars(cells[i].data(), cells[i].data() + cells[i].size(), doub);
				sCol->vals.push_back(doub);
			}
			colIndex++;
		}
	}

	
}

void printAgg() {
	Col* groupByCol = nullptr;
	vector<AggCol> aggCols;

	// SELECT prijmeni, SUM(jmeno), MIN(key), MAX(key), MIN(vek), MAX(vek), SUM(deti), SUM(rodice), MIN(prumer), MAX(prumer) GROUP_BY prijmeni

	// Process query
	string word;
	while (cin >> word) {
		if (word == "") continue;
		if (word == "SELECT") continue;

		if (word.back() == ',') {
			word.pop_back();
		}

		if (word == "GROUP_BY") {
			cin >> word;
			groupByCol = getCol(word);
		}
		else {
			ColAggFun aggFun = strToAggFun(string_view(word.c_str(), 3));
			string colName = aggFun == ColAggFun::None ? word : word.substr(4, word.size() - 5);
			aggCols.emplace_back(word, getCol(colName), aggFun);
		}
	}

	// Group
	map<string, vector<size_t>> groups;
	vector<string> groupsOrd;
	if (groupByCol != nullptr) {
		size_t counter = 0;
		if (groupByCol->m_dataType == ColDataType::String) {
			StringCol* sCol = dynamic_cast<StringCol*>(groupByCol);
			for (string& val : sCol->vals) {
				if (groups.count(val) == 0) groupsOrd.push_back(val);
				groups[val].push_back(counter++);
				
			}
		}
		else if (groupByCol->m_dataType == ColDataType::Int) {
			IntCol* sCol = dynamic_cast<IntCol*>(groupByCol);
			for (int val : sCol->vals) {
				string str = to_string(val);
				if (groups.count(str) == 0) groupsOrd.push_back(str);
				groups[str].push_back(counter++);
			}
		}
		else if (groupByCol->m_dataType == ColDataType::Double) {
			DoubleCol* sCol = dynamic_cast<DoubleCol*>(groupByCol);
			for (double val : sCol->vals) {
				string str = to_string(val);
				if (groups.count(str) == 0) groupsOrd.push_back(str);
				groups[str].push_back(counter++);
			}
		}
	}
	
	// Print cols
	size_t colCounter = 0;
	for (const AggCol& col : aggCols) {
		if (colCounter > 0) cout << ";";
		cout << col.m_name;
		colCounter++;
	}

	// Print rows
	for (const string& groupKey : groupsOrd) {
		vector<size_t> group = groups.at(groupKey);
		cout << endl;
		colCounter = 0;
		for (const AggCol& col : aggCols) {
			if (colCounter > 0) cout << ";";

			if (col.m_origCol == groupByCol) {
				cout << groupKey;
			}
			else if (col.m_origCol->m_dataType == ColDataType::String) {
				StringCol* sCol = dynamic_cast<StringCol*>(col.m_origCol);
				string_view val;
				size_t rowCounter = 0;
				for (size_t row : group) {
					if (rowCounter == 0) val = sCol->vals[row];
					if (col.m_aggFun == ColAggFun::Sum) cout << sCol->vals[row];
					else if (col.m_aggFun == ColAggFun::Min) val = sCol->vals[row] < val ? sCol->vals[row] : val;
					else if (col.m_aggFun == ColAggFun::Max) val = sCol->vals[row] > val ? sCol->vals[row] : val;
					else val = sCol->vals[row];
					rowCounter++;
				}
				if (col.m_aggFun != ColAggFun::Sum) cout << val;
			}
			else if(col.m_origCol->m_dataType == ColDataType::Int) {
				IntCol* sCol = dynamic_cast<IntCol*>(col.m_origCol);
				int val = 0;
				size_t rowCounter = 0;
				for (size_t row : group) {
					if (rowCounter == 0) val = sCol->vals[row];
					else if (col.m_aggFun == ColAggFun::Sum) val += sCol->vals[row];
					else if (col.m_aggFun == ColAggFun::Min) val = min(val, sCol->vals[row]);
					else if (col.m_aggFun == ColAggFun::Max) val = max(val, sCol->vals[row]);
					else val = sCol->vals[row];
					rowCounter++;
				}
				cout << to_string(val);
			}
			else if (col.m_origCol->m_dataType == ColDataType::Double) {
				DoubleCol* sCol = dynamic_cast<DoubleCol*>(col.m_origCol);
				double val = 0;
				size_t rowCounter = 0;
				for (size_t row : group) {
					if (rowCounter == 0) val = sCol->vals[row];
					else if (col.m_aggFun == ColAggFun::Sum) val += sCol->vals[row];
					else if (col.m_aggFun == ColAggFun::Min) val = min(val, sCol->vals[row]);
					else if (col.m_aggFun == ColAggFun::Max) val = max(val, sCol->vals[row]);
					else val = sCol->vals[row];
					rowCounter++;
				}
				cout << to_string(val);
			}
			
			colCounter++;
		}
	}
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
	int ret = mainRecodex();
	for (Col* col : cols) {
		delete col;
	}
	return ret;
}