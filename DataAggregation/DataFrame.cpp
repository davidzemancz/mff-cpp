#include "DataFrame.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

DataFrame::DataFrame()
{

}

void DataFrame::addCol(const DataFrameCol& col)
{	
	cols.insert({ col.m_name, col });
}

void DataFrame::updateColDataType(const string& name, const ColDataType dataType) {
	cols.at(name).m_dataType = dataType;
}

void DataFrame::addRowVctr(const vector<string>& rowVctr) 
{
	rows.push_back(rowVctr);
}

DataFrame DataFrame::apply(const string& query) {
	DataFrame df;
	string groupBy;
	vector<string> selects;

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
			ColAggFun aggFun = StrToAggFun(aggFunStr);
			string colName = aggFun == ColAggFun::None ? word : word.substr(4, word.size() - 5);
			df.addCol(DataFrameCol(count++, word, cols.at(colName).m_dataType, aggFun, colName));
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
		vector<string> aggRow;
		for (const string& select : selects) {
			DataFrameCol col = df.cols.at(select);
			size_t colIndex = cols.at(col.m_tag).m_pos;
			ColDataType colDt = col.m_dataType;
			size_t counter = 0;
			if (colDt == ColDataType::String) {
				string value;
				for (const vector<string>& row : group.second) {
					if (counter == 0) value = row[colIndex];
					else if (col.m_aggFun == ColAggFun::Sum) value += row[colIndex];
					else value = row[colIndex];
					counter++;
				}
				aggRow.push_back(value);
			}
			else if (colDt == ColDataType::Int) {
				int value; 
				for (const vector<string>& row : group.second) {
					if (counter == 0) value = stoi(row[colIndex]);
					else if (col.m_aggFun == ColAggFun::Sum) value += stoi(row[colIndex]);
					else if (col.m_aggFun == ColAggFun::Min) value = min(stoi(row[colIndex]), value);
					else if (col.m_aggFun == ColAggFun::Max) value = max(stoi(row[colIndex]), value);
					counter++;
				}
				aggRow.push_back(to_string(value));
			}
			else if (colDt == ColDataType::Double) {
				double value;
				for (const vector<string>& row : group.second) {
					if (counter == 0) value = stod(row[colIndex]);
					else if (col.m_aggFun == ColAggFun::Sum) value += stod(row[colIndex]);
					else if (col.m_aggFun == ColAggFun::Min) value = min(stod(row[colIndex]), value);
					else if (col.m_aggFun == ColAggFun::Max) value = max(stod(row[colIndex]), value);
					counter++;
				}
				aggRow.push_back(to_string(value));
			}
		}
		df.addRowVctr(aggRow);
	}
	
	return df;
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


