#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <fstream>
#include "Student.h"
#include "DuplicateSubjectException.h"
#include "OutOfRangeException.h"
#include "SubjectNotFound.h"
#include "IPupil.h"
#include "SchoolBoy.h"
#include "Pupils.h"

using namespace std;

#define inf 10000000007
#define EDIT_BY_POSITION 1
#define USING_EXCEPTION 1

int main() {
	SchoolBoy q;
	//q.SetSubject();
	q.SetMarkOfSubjectByPos();
	Pupils p;
	for (auto& i : p.AverageScore(q)) {
		cout << i.first << " " << i.second << endl;
	}
	p.GetData(q);
	//q.out();
	return 0;
}