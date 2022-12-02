#include "DataFrame.h"
#include <iostream>
#include <sstream>
#include <vector>

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

	// SELECT prijmeni, SUM(jmeno), MIN(key), MAX(key), MIN(vek), MAX(vek), SUM(deti), SUM(rodice), MIN(prumer), MAX(prumer) GROUP_BY prijmeni

	const string SELECT = "SELECT";
	const string GROUP_BY = "GROUP_BY";
	const string MIN = "MIN";
	const string MAX = "MAX";
	const string SUM = "SUM";

	string select;
	string groupBy;
	vector<string> aggs;
 
	stringstream ss(query);
	string prevWord;
	string word;

	int count = 0;
	while (ss >> word) {
		if (word == "") continue;

		if (word.back() == ',') {
			word.pop_back();
		}

		if (word == SELECT) {
			prevWord = SELECT;
		}
		else if (word == GROUP_BY) {
			prevWord = GROUP_BY;
		}
		else if (prevWord == SELECT) {
			select = word;
			prevWord = "";
		}
		else if (prevWord == GROUP_BY) {
			groupBy = word;
			prevWord = "";
		}
		else {
			aggs.push_back(word);
		}
	}
		

	
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


