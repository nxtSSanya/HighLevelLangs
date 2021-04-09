#pragma once
#define EDIT_BY_POSITION 1
#define USING_EXCEPTION 1
#include "IPupil.h"
#include "Student.h"
#include "DuplicateSubjectException.h"
#include "OutOfRangeException.h"
#include "SubjectNotFound.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>

using namespace std;

class SchoolBoy : public IPupil { 
private:
	class Register  { 
		string name_2;
		map< string, vector<int> > marks;
	public:
		Register(string name_2, string subject, vector<int>& values) { 
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
		void GetData() {
			for (auto& i : this->marks) {
				cout << "Subject "s << i.first << " marks: "s;
				for (auto& j : i.second) {
					cout << j << " ";
				}
				cout << endl;
			}
		}
		map<string, vector<int> > GetMap() {
			return this->marks;
		}
		void GetSubjectById() {
			int id;
			cout << "Enter ID of a Subject: "s;
			cin >> id;
			cout << endl;
			try {
				if (id > this->marks.size()) {
					throw OutOfRangeException("ID is out of range!");
				}
				else {
					int kol = 0;
					for (auto& i : this->marks) {
						if (kol == id) {
							cout << i.first << endl;
						}
						kol++;
					}
				}
			}
			catch (OutOfRangeException & ex) {
				cout << ex.what() << endl;
				return;
			}
		}
		void GetOnlySubjects() {
			for (auto& i : this->marks) {
				cout << i.first << endl;
			}
		}
		void SetName(string name) {
			this->name_2 = name;
		}
		void EditSubjectByName(string search, string subject) {
			try {
				auto it = this->marks.find(search);
				if (it != this->marks.end()) {
					this->marks[subject] = it->second;
					marks.erase(it);
				}
				else {
					throw SubjectNotFound("Subject not found!"s);
				}
			}
			catch (SubjectNotFound & exc) {
				cout << exc.what() << endl;
				return;
			}
		}
		void EditValueOfSubjectByPos(int pos, int value, string subject) {	
			try {
				auto it = this->marks.find(subject);
				if (it == this->marks.end()) {
					throw exception("Subject not found!");
				}
				if (pos >= it->second.size() || pos < 0) {
					throw OutOfRangeException("Vector is out of range!"s);
				}	
				else {
					for (auto& mark : this->marks) {
						if (mark.first == subject) {
							mark.second[pos] = value;
						}
					}/*it->second[pos] = value;*/
				}
			}
			catch (OutOfRangeException & ex) {
				cout << ex.what() << endl;
				return;
			}
			catch (exception & ex) {
				cout << ex.what() << endl;
				return;
			}
		}
		void GetMarkByIndex(int index, string subject) {
			try {
				auto it = this->marks.find(subject);
				if (it != this->marks.end()) {
					if (index >= it->second.size() || index < 0) {
						throw OutOfRangeException("Vector is out of range!"s);
					}
					else {
						cout << "Value at position "s << index << " at subject "s << subject << " is "s << it->second[index] << endl;
					}
				}
			}
			catch (OutOfRangeException & ex) {
				cout << ex.what() << endl;
				return;
			}
		}
		void ResetTheVector(vector<int>& nV, string subject) {
			if (!nV.empty()) {
				cout << "Vector is empty!" << endl;
				return;
			}
			this->marks[subject] = nV;
		}
		void SetNewValue(string subject, int n) {
			vector<int> v(n);
			cout << "Enter marks of subject "s << subject << endl;
			for (auto& i : v) {
				cin >> i;
			}
			this->marks.insert({ subject, v });
		}
		void GetSizes() {
			cout << "Subjects are: "s << this->GetSize().first << endl;
			cout << "All subjects are: "s << this->GetSize().second << endl;
		}
	private:
		pair< int, int > GetSize() {
			int cnt = 0;
			for (auto& i : this->marks) {
				if (!i.second.empty()) {
					cnt++;
				}
			}
			pair<int, int> ans = { this->marks.size(), cnt };
		return ans;
		}	
	};
	vector<Register> data;
public:
	SchoolBoy() {
		int count = 0;
		ifstream f("data.txt"s);
		int t, sub;
		vector<string> subjects;
		f >> t;
		while (t--) {
			string name, subject;
			vector<int> values;
			map<string, vector<int> > tmp;
			f >> name;
			f >> sub;
			while (sub--) {
				int n;
				f >> subject >> n;
				for (int i = 0; i < n; ++i) {
					int tmp;
					f >> tmp;
					values.push_back(tmp);
				}
				tmp.insert({ subject, values });
				values.clear();
			}
			data.push_back(Register(name, tmp));
			++count;
		}
	}
#if EDIT_BY_POSITION == 1
	void SetSecondName() override {
		int pos;
		string name;
		cout << "Enter ID of a student and name to change: "s;
		cin >> pos >> name;
		try {
			if (pos < 0 || pos >= data.size()) {
				throw OutOfRangeException("Vector is out of range!"s);
			}
		}
		catch (OutOfRangeException & ex) {
			cout << ex.what() << endl;
		}
		cout << endl;
		data[pos].SetName(name);
	}
	void SetSubject() override {
		int pos;
		string subject, search_;
		cout << "Enter ID of a student, subject to change and subject that u want to change: "s;
		cin >> pos >> subject >> search_;
		try {
			if (pos < 0 || pos >= data.size()) {
				throw OutOfRangeException("Vector is out of range!"s);
			}
			else {
				cout << endl;
				data[pos].EditSubjectByName(search_, subject);
			}
		}
		catch (OutOfRangeException & ex) {
			cout << ex.what() << endl;
		}
		
	}
	void SetMarkOfSubjectByPos() override {
		int DataPos, value, SubjectPos;
		string subject;
		cout << "Enter ID of a student, position of mark, value to change and subject: "s;
		cin >> DataPos >> SubjectPos >> value >> subject;
		try {
			if (DataPos < 0 || DataPos >= data.size()) {
				throw OutOfRangeException("Vector is out of range!"s);
			}
			else {
				cout << endl;
				data[DataPos].EditValueOfSubjectByPos(SubjectPos, value, subject);
			}
		}
		catch (OutOfRangeException & ex) {
			cout << ex.what() << endl;
		}

	}
	void SetNewVectorOfMarks() override {
		vector<int> v;
		int pos, n;
		string subject;
		cout << "Enter size of new vector, ID of a student and subject: "s;
			cin >> n >> pos >> subject;
			try {
				if (pos < 0 || pos >= data.size()) {
					throw OutOfRangeException("Vector is out of range!"s);
				}
				else {
					for (auto& i : v) cin >> i;
					cout << endl;
					data[pos].ResetTheVector(v, subject);
				}
			}
			catch (OutOfRangeException & ex) {
				cout << ex.what() << endl;
			}

	}
	void SetNewTable() override {
		string subject;
		int n, pos;
		cout << "Enter size of vector with marks, ID of a student and subject: "s;
		cin >> n >> pos >> subject;
		try {
			if (pos < 0 || pos >= data.size()) {
				throw OutOfRangeException("Vector is out of range!"s);
			}
			else {
				cout << endl;
				data[pos].SetNewValue(subject, n);
			}
		}
		catch (OutOfRangeException & ex) {
			cout << ex.what() << endl;
		}

	}
#endif
	void GetOnlySubjects() override {
		int pos;
		cout << "Enter ID of a student: "s;
		cin >> pos;
		try {
			if (pos < 0 || pos >= data.size()) {
				throw OutOfRangeException("Vector is out of range!"s);
			}
			else {
				cout << endl;
				data[pos].GetOnlySubjects();
				cin.clear();
			}
		}
		catch (OutOfRangeException & ex) {
			cout << ex.what() << endl;
		}

	}
	void GetOnlyName() override {
		int pos;
		cout << "Enter ID of a student: "s;
		cin >> pos;
		try {
			if (pos < 0 || pos >= data.size()) {
				throw OutOfRangeException("Vector is out of range!"s);
			}
			else {
				cout << endl;
				data[pos].GetName();
				cin.clear();
			}
		}
		catch (OutOfRangeException & ex) {
			cout << ex.what() << endl;
		}

	}
	void GetValueOfMarks() override {
		int index, pos;
		string subject;
		cout << "Enter index of mark, ID of a student and subject: "s;
		cin >> index >> pos >> subject;
		try {
			if (pos < 0 || pos >= data.size()) {
				throw OutOfRangeException("Vector is out of range!"s);
			}
			else {
				cout << endl;
				data[pos].GetMarkByIndex(index, subject);
				cin.clear();
			}
		}
		catch (OutOfRangeException & ex) {
			cout << ex.what() << endl;
		}

	}
	void GetAllData() override {
		for (auto& i : data) {
			i.GetName();
			i.GetData();
		}
	}
	void GetSubjectById() override {
		int pos;
		cout << "Enter ID of a student: "s;
		cin >> pos;
		try {
			if (pos < 0 || pos >= data.size()) {
				throw OutOfRangeException("Vector is out of range!"s);
			}
			else {
				cout << endl;
				data[pos].GetSubjectById();
				cin.clear();
			}
		}
		catch (OutOfRangeException & ex) {
			cout << ex.what() << endl;
		}

	}
	map<string, vector<int> > GetMarksOfStudent() override {
		int pos;
		cout << "Enter ID of a student: "s;
		cin >> pos;
		try {
			if (pos < 0 || pos >= data.size()) {
				throw OutOfRangeException("Vector is out of range!"s);
			}
			else {
				cout << endl;
				return data[pos].GetMap();
				cin.clear();
			}
		}
		catch (OutOfRangeException & ex) {
			cout << ex.what() << endl;
		}

	}
	void GetSizes() override {
		int pos;
		cout << "Enter ID of a student: "s;
		cin >> pos;
		try {
			if (pos < 0 || pos >= data.size()) {
				throw OutOfRangeException("Vector is out of range!"s);
			}
			else {
				cout << endl;
				data[pos].GetSizes();
				cin.clear();
			}
		}
		catch (OutOfRangeException & ex) {
			cout << ex.what() << endl;
		}
		
	}
};