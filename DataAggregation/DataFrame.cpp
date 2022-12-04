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

void DataFrame::printAgg(const string& query) {
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
	map<string, vector<size_t>> groups;
	for (size_t r = 0; r < rows.size(); r++) {
		groups[rows[r][groupByIndex]].push_back(r);
	}
	

	// Print cols
	size_t colCounter = 0;
	for (const string& select : selects) {
		DataFrameCol col = df.cols.at(select);
		if (colCounter > 0) cout << ";";
		cout << col.m_name;
		colCounter++;
	}

	// Aggregate rows
	for (const auto& group : groups) {
		colCounter = 0;
		cout << endl;
		for (const string& select : selects) {
			DataFrameCol col = df.cols.at(select);
			size_t colIndex = cols.at(col.m_tag).m_pos;
			ColDataType colDt = col.m_dataType;
			size_t rowCounter = 0;
			if (colDt == ColDataType::String) {
				string value;
				for (const size_t r : group.second) {
					if (rowCounter == 0) value = rows[r][colIndex];
					else if (col.m_aggFun == ColAggFun::Sum) value += rows[r][colIndex];
					else value = rows[r][colIndex];
					rowCounter++;
				}

				// Print
				if (colCounter > 0) cout << ";";
				cout << value;
				colCounter++;
			}
			else if (colDt == ColDataType::Int) {
				int value = 0; 
				for (const size_t r : group.second) {
					if (rowCounter == 0) value = stoi(rows[r][colIndex]);
					else if (col.m_aggFun == ColAggFun::Sum) value += stoi(rows[r][colIndex]);
					else if (col.m_aggFun == ColAggFun::Min) value = min(stoi(rows[r][colIndex]), value);
					else if (col.m_aggFun == ColAggFun::Max) value = max(stoi(rows[r][colIndex]), value);
					rowCounter++;
				}
				
				// Print
				if (colCounter > 0) cout << ";";
				cout << to_string(value);
				colCounter++;
			}
			else if (colDt == ColDataType::Double) {
				double value = 0.0;
				for (const size_t r : group.second) {
					if (rowCounter == 0) value = stod(rows[r][colIndex]);
					else if (col.m_aggFun == ColAggFun::Sum) value += stod(rows[r][colIndex]);
					else if (col.m_aggFun == ColAggFun::Min) value = min(stod(rows[r][colIndex]), value);
					else if (col.m_aggFun == ColAggFun::Max) value = max(stod(rows[r][colIndex]), value);
					rowCounter++;
				}
				
				// Print
				if (colCounter > 0) cout << ";";
				cout << to_string(value);
				colCounter++;
			}
		}
	}
}



