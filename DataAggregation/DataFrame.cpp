#include "DataFrame.h"
#include <iostream>

using namespace std;

DataFrame::DataFrame()
{

}

void DataFrame::addCol(const DataFrameCol& col)
{	
	cols.push_back(col);
}

void DataFrame::addRowVctr(const vector<string>& rowVctr) 
{
	rows.push_back(rowVctr);
}

DataFrame& DataFrame::apply(const string& query) {
	DataFrame df;

	return *this;
}

void DataFrame::debugPrint() const
{
	printf("----- Cols -----");
	printf("\n");
	for (const auto& col : cols)
	{
		string line = col.m_name + " " + to_string((int)(col.m_dataType)) + " " + to_string(col.m_pos) + "\n";
		printf(line.c_str());
	}

	printf("----- Rows -----");
	for (const auto& row : rows)
	{
		for (const string& elem : row) {
			printf(elem.c_str());
			printf(";");
		}
		printf("\n");
	}
}
