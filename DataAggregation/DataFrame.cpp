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
	cols.insert({ col.m_name, col });
}

void DataFrame::addRowVctr(const vector<string>& rowVctr) 
{
	rows.push_back(rowVctr);
}

DataFrame& DataFrame::apply(const string& query) {
	DataFrame df;
	string groupBy;
	vector<string> selects;

	// SELECT prijmeni, SUM(jmeno), MIN(key), MAX(key), MIN(vek), MAX(vek), SUM(deti), SUM(rodice), MIN(prumer), MAX(prumer) GROUP_BY prijmeni
	
	// Consts
	const string SELECT = "SELECT";
	const string GROUP_BY = "GROUP_BY";
	const string MIN = "MIN";
	const string MAX = "MAX";
	const string SUM = "SUM";

	// Process query
	stringstream ss(query);
	string word;
	int count = 0;
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
			selects.push_back(word);
		}
	}
	
	// Groups
	size_t groupByIndex = cols.at(groupBy).m_pos;
	map<string, vector<vector<string>>> groups;
	for (const vector<string>& row : rows) {
		groups[row[groupByIndex]].push_back(row);
	}

	// Aggregate
	for (const auto& group : groups) {
		for (const string& select : selects) {

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
		string line = col.second.m_name + " " + to_string((int)(col.second.m_dataType)) + " " + to_string(col.second.m_pos) + "\n";
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


