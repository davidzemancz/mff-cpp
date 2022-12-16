#include "Storage.h"

TypeEnum Storage::GetType(const string& name) const
{
    return types.at(name);
}

 int  Storage::GetInt(const string& name) const
{
     return intVals.at(name);
}

 void Storage::SetInt(const string& name, const int value)
 {
     intVals[name] = value;
 }

float Storage::GetFloat(const string& name) const
{
    return floatVals.at(name);
}

void Storage::SetFloat(const string& name, const float value)
{
    floatVals[name] = value;
}

double Storage::GetDouble(const string& name) const
{
    return doubleVals.at(name);
}

void Storage::SetDouble(const string& name, const double value)
{
    doubleVals[name] = value;
}
