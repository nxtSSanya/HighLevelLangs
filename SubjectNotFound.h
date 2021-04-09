#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class SubjectNotFound :public exception
{
private: string error_code;
public:
	SubjectNotFound(string error) :error_code(error) {}
	string what() {
		return error_code;
	}
};

