#pragma once
#include <string>
#include <map>
#include <vector>

using namespace std;

class IPupil
{
public:
	void virtual SetSecondName() = 0;
	void virtual SetSubject() = 0;
	void virtual SetMarkOfSubjectByPos() = 0;
	void virtual SetNewVectorOfMarks() = 0;
	void virtual SetNewTable() = 0;
	void virtual GetOnlySubjects() = 0;
	void virtual GetOnlyName() = 0;
	void virtual GetValueOfMarks() = 0;
	void virtual GetAllData() = 0;
	map<string, vector<int> > virtual GetMarksOfStudent() = 0;
	void virtual GetSubjectById() = 0;
	void virtual GetSizes() = 0;
};

