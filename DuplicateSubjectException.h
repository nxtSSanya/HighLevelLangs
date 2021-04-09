#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class DuplicateSubjectException :public exception
{
private: string error_code;
public:
	DuplicateSubjectException(string error) :error_code(error) {}
	string what() {
		return error_code;
	}
};

