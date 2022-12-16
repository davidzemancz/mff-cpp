#pragma once
#include <string>

using namespace std;
#include <map>

enum class TypeEnum { Int, Float, Double };

class Storage
{
private:
	map<string, TypeEnum> types;
	map<string, int> intVals;
	map<string, float> floatVals;
	map<string, double> doubleVals;

public:
	TypeEnum GetType(const string& name) const;
	int GetInt(const string& name) const;
	void SetInt(const string& name, const int value);
	float GetFloat(const string& name) const;
	void SetFloat(const string& name, const float value);
	double GetDouble(const string& name) const;
	void SetDouble(const string& name, const double value);

};

