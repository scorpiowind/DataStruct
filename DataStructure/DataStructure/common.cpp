#include "pch.h"
#include "common.h"
#include <random>

using namespace std;
void common::genRandomInt(vector<int> &vRand, int len, int minValue, int maxValue)
{
	random_device rd;
	default_random_engine eng(rd());
	vRand.clear(); vRand.reserve(len);
	for (auto i = 0; i < len; ++i)
	{
		int tmpValue = eng() % (maxValue - minValue + 1) + minValue;
		vRand.emplace_back(tmpValue);
	}
}

ostream& common::operator <<(ostream &out, vector<int> &data)
{
	for (int num : data)
		out << num << " ";
	out << endl;
	return out;
}