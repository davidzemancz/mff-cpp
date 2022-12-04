#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "DataFrameCol.h"

using namespace std;

class DataFrame
{

public:
	unordered_map<string, DataFrameCol> cols;
	vector<vector<string>> rows;

	DataFrame();
	void addCol(const DataFrameCol& col);
	void updateColDataType(const string& name, const ColDataType dataType);
	void addRowVctr(const vector<string>& rowVctr);
	void printAgg(const string& query);
};