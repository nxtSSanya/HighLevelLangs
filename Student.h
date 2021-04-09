#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include "IPupil.h"
#include "DuplicateSubjectException.h"
#include "OutOfRangeException.h"
#include "SubjectNotFound.h"

using namespace std;

class Student : public IPupil{
private:
	string name_2;
	map <string, vector <int> > marks;

public:
	Student(string name_2) {
		this->name_2 = name_2;
	}
	Student(string name_2, const map<string, vector <int> >& marks) {
		this->name_2 = name_2;
		this->marks = marks;
	}
	void SetSecondName() override {
		string name_2;
		cin >> name_2;
		if (!name_2.empty()) {
			this->name_2 = name_2;
		}
		else {
			cout << "Error parsing second name" << endl;
		}
	}
	map<string, vector<int> > GetMarksOfStudent() override {
		return this->marks;
	}
	void SetMarkOfSubjectByPos() override {
		int pos;
		int value;
		string subject;
		cin >> pos >> value >> subject;
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
	void GetOnlySubjects() override {
		for (auto& sub : this->marks) {
			cout << sub.first << endl;
		}
	}
	void GetSubjectById() override {
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
	void SetSubject() override {
		string search;
		string subject;
		cout << "Enter subject that u want to change and new subject: "s;
		cin >> search >> subject;
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
	void GetSizes() override {
		this->GetInfoMap();
	}
	void SetNewTable () override {
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