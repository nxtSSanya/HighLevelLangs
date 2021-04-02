#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

#define inf 10000000007
#define EDIT_BY_POSITION 1

class Student {
private:
	string name_2;
	map <string, vector <int> > marks;
	
public:
	Student(string name_2) {
		this->name_2 = name_2;
	}
	void GetSecondName() {
		cout << this->name_2 << endl;
	}
	void SetSecondName() {
		string name_2;
		cin >> name_2;
		if (!name_2.empty()) {
			this->name_2 = name_2;
		}
		else {
			cout << "Error parsing second name" << endl;
		}
	}
	void GetMarksOfStudent() {
		for (auto& mark : this->marks) {
			cout << mark.first << ": ";
			for (auto& values : mark.second) {
				cout << values << " ";
			}
		}
	}
	void SetMarkOfStudentByPos() {
		int pos;
		int value;
		string subject;
		cin >> pos >> value >> subject;
		for (auto& mark : this->marks) {
			if (mark.first == subject) {
				mark.second[pos] = value;
			}
		}
	}
	void GetOnlySubjects() {
		for (auto& sub : this->marks) {
			cout << sub.first << endl;
		}
	}
	void GetSubjectById() {
		int id;
		cin >> id;
		int kol = 0;
		for (auto& i : this->marks) {
			if (kol == id) {
				cout << i.first << endl;
			}
			kol++;
		}
	}
	void SetSubjectByName() {
		string search;
		string subject;
		cin >> search >> subject;
		auto it = this->marks.find(search);
		if (it != this->marks.end()) {
			this->marks[subject] = it->second;
			marks.erase(it);
		}
	}
	void SetMap() {
		int t;
		cin >> t;
		while (t--) {
			string subject;
			int sz;
			cin >> subject >> sz;
			vector<int> input(sz);
			for (auto& i : input) {
				cin >> i;
			}
			this->marks[subject] = input;
		}
	}
	void GetSizes() {
		this->GetInfoMap();
	}
	void SetNewValue() {
		string subject;
		int n;
		cin >> subject >> n;
		vector<int> v(n);
		for (auto& i : v) {
			cin >> i;
		}
		this->marks.insert({ subject, v });
	}

private:
	void GetInfoMap() {
		cout << this->marks.size() << endl;
		for (auto& out : this->marks) {
			cout << out.second.size() << endl;
		}
	}
};

class SchoolBoy { // много школьников
private:
	class Register { // инфа по каждому школьнику
		string name_2;
		map< string, vector<int> > marks;
	public:
		Register(string name_2, string subject, vector<int>& values) { // пушим в класс инфу
			this->name_2 = name_2;
			this->marks.insert({ subject, values });	
		}
		Register(string name_2, map<string, vector<int> >& mp) {
			this->name_2 = name_2;
			this->marks = mp;
		}
		void GetName() {
			cout << this->name_2 << endl;
		}
		void GetData() { // получаем данные по каждому школьнику
			for (auto& i : this->marks) {
				cout << "Subject " << i.first << " marks: ";
				for (auto& j : i.second) {
					cout << j << " ";
				}
				cout << endl;
			}
		}
		void GetOnlySubjects() {
			for (auto& i : this->marks) {
				cout << i.first << endl;
			}
		}
		void EditName(string name) {
			this->name_2 = name;
		}
		void EditSubjectByName(string search, string subject) {
			auto it = this->marks.find(search);
			if (it != this->marks.end()) {
				this->marks[subject] = it->second;
				marks.erase(it);
			}
		}
		void EditValueOfSubjectByPos(int pos, int value, string subject) {			
			for (auto& mark : this->marks) {
				if (mark.first == subject) {
					mark.second[pos] = value;
				}
			}
		}
		void ResetTheVector(vector<int>& nV, string subject) {
			this->marks[subject] = nV;
		}
		void SetNewValue(string subject, int n) {
			vector<int> v(n);
			cout << "Enter marks of subject " << subject << endl;
			for (auto& i : v) {
				cin >> i;
			}
			this->marks.insert({ subject, v });
		}
	};
	vector<Register> data;
public:
	SchoolBoy(int t) {	// пушим инфу типа Регистр
		int count = 0;
		while (t--) {
			string name;
			string subject;
			vector<int> values;
			map<string, vector<int> > tmp;
			cout << "Enter second name of Schoolboy " << count << endl;
			cin >> name;
			int sub;
			cout << "Enter the number of subjects for schoolboy " << name << endl;
			cin >> sub;
			while (sub--) {
				cout << "Enter subject and nubmer of marks" << endl;
				int n;
				cin >> subject >> n;
				cout << endl;
				cout << "Enter the values of this subject" << endl;
				for (int i = 0; i < n; ++i) {
					int tmp;
					cin >> tmp;
					values.push_back(tmp);
				}
				tmp.insert({ subject, values });		
				values.clear();			
			}
			data.push_back(Register(name, tmp));
			++count;
		}
	}
#ifdef EDIT_BY_POSITION
	void EditNameOfSchoolboyById(int pos, string name) {
		data[pos].EditName(name);
	}
	void EditSubjectById(int pos, string subject, string search) {
		data[pos].EditSubjectByName(search, subject);
	}
	void EditValueOfSubjectByPos(int DataPos, int value, string subject, int SubjectPos) {
		data[DataPos].EditValueOfSubjectByPos(SubjectPos, value, subject);
	}
	void SetNewVectorOfMarks(vector<int>& v, int pos, string subject) {
		data[pos].ResetTheVector(v, subject);
	}
	void SetNewSchoolboy(string subject, int n, int pos) {
		data[pos].SetNewValue(subject, n);
	}
#endif
	void OutSubjectsOfSchoolboyByPos(int pos) {
		data[pos].GetOnlySubjects();
	}
	void OutOnlyName(int pos) {
		data[pos].GetName();
	}
	void OutIdOfVector() {
		for (size_t size = 0; size < data.size(); ++size) {
			cout << "ID: " << size << " Name: ";
			OutOnlyName(static_cast<int>(size));
		}
	}
	void out() {
		bool f = 0;
		for (auto& i : data) {
			if (f == 0) {
				i.GetName();
				f = 1;
			}
			i.GetData();
		}
	}
};
