#pragma once
#include <iostream>
#include <exception>
#include <vector>
#include <algorithm>

using namespace std;

class OutOfRangeException :public exception
{
private:
	string error_code;
public:
	OutOfRangeException(string error):error_code(error){}
	string what() {
		return error_code;
	}
};

