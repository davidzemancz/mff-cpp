#pragma once
#include <string>
#include <map>
#include <vector>
#include "DataFrameCol.h"

using namespace std;

class DataFrame
{
private:
	map<string, DataFrameCol> cols;
	vector<vector<string>> rows;
public:
	DataFrame();
	void addCol(const DataFrameCol& col);
	void addRowVctr(const vector<string>& rowVctr);
	DataFrame& apply(const string& query);
	void debugPrint() const;
};