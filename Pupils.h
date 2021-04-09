#pragma once
#include "IPupil.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
class Pupils
{
public:
	static void GetData(IPupil& pupil) {
		pupil.GetAllData();
	}
	static map <string, double> AverageScore(IPupil& pupil) {
		map<string, double > ans;
		for (auto& i : pupil.GetMarksOfStudent()) {
			double cur = 0.;
			for (auto& j : i.second) {
				cur += j * (1. / static_cast<int>(i.second.size()));
			}
			ans.insert({ i.first, cur});
		}
		return ans;
	}
};

