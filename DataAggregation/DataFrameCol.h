#pragma once
#include <string>

enum class ColDataType { Int = 1, String = 2, Double = 3 };

class DataFrameCol
{

public:
	size_t m_pos;
	std::string m_name;
	ColDataType m_dataType;
	
	DataFrameCol(const size_t pos, const std::string& name, const ColDataType dataType);
};

