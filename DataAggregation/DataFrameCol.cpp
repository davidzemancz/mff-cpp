#include "DataFrameCol.h"
#include <string>
#include <cstring>

using namespace std;

ColDataType StrToDataType(string& str) {
	if (strcmp(str.c_str(), "string") == 0) return ColDataType::String;
	else if (strcmp(str.c_str(), "int") == 0) return ColDataType::Int;
	else if (strcmp(str.c_str(), "double") == 0) return ColDataType::Double;
	return ColDataType::Unknown;
}
ColAggFun StrToAggFun(string& str) {
	if (strcmp(str.c_str(), "SUM") == 0) return ColAggFun::Sum;
	else if (strcmp(str.c_str(), "MIN") == 0) return ColAggFun::Min;
	else if (strcmp(str.c_str(), "MAX") == 0) return ColAggFun::Max;
	return ColAggFun::None;
}

DataFrameCol::DataFrameCol() { }

DataFrameCol::DataFrameCol(const size_t pos, const std::string& name, const ColDataType dataType)
	: m_pos(pos), m_name(name), m_dataType(dataType)
{

}

DataFrameCol::DataFrameCol(const size_t pos, const std::string& name, const ColDataType dataType, const ColAggFun aggFun) 
	: m_pos(pos), m_name(name), m_dataType(dataType), m_aggFun(aggFun)
{

}

DataFrameCol::DataFrameCol(const size_t pos, const std::string& name, const ColDataType dataType, const ColAggFun aggFun, const string& tag)
	: m_pos(pos), m_name(name), m_dataType(dataType), m_aggFun(aggFun), m_tag(tag)
{

}