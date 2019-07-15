#pragma once
#include <vector>

using namespace std;
namespace common
{
	void genRandomInt(vector<int> &vRand, int len = 16, int minValue = 0, int maxValue = INT32_MAX);
	ostream& operator <<(ostream &out, vector<int> &data);
}