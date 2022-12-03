#pragma once
#include <string>

using namespace std;

enum class ColDataType { Unknown = 0, Int = 1, String = 2, Double = 3 };
enum class ColAggFun { None = 0, Sum = 1, Min = 2, Max = 3 };

ColDataType StrToDataType(string& str);
ColAggFun StrToAggFun(string& str);

class DataFrameCol
{

public:
	size_t m_pos;
	string m_name;
	ColDataType m_dataType;
	ColAggFun m_aggFun;
	string m_tag;
	
	DataFrameCol();
	DataFrameCol(const size_t pos, const std::string& name, const ColDataType dataType);
	DataFrameCol(const size_t pos, const std::string& name, const ColDataType dataType, const ColAggFun aggFun);
	DataFrameCol(const size_t pos, const std::string& name, const ColDataType dataType, const ColAggFun aggFun, const string& tag);
};

