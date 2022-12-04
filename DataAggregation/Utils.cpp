#include "Utils.h"
#include <string>
#include <vector>

using namespace std;

vector<string> strSplit(string str, string token) {
	vector<string>result;
	while (str.size()) {
		size_t index = str.find(token);
		if (index != string::npos) {
			result.push_back(str.substr(0, index));
			str = str.substr(index + token.size());
			if (str.size() == 0) result.push_back(str);
		}
		else {
			result.push_back(str);
			str = "";
		}
	}
	return result;
}
