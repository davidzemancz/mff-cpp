#include "DataFrameCol.h"

DataFrameCol::DataFrameCol(const size_t pos, const std::string& name, const ColDataType dataType)
	: m_pos(pos), m_name(name), m_dataType(dataType)
{

}