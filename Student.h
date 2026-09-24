#pragma once
#include "lib.h"

class Student {
private:
    string name, surname;
    vector <int> Points;
    int exam;
    double final;
public:
    Student();
    Student(string n, string s, vector<int> P, int E);
    ~Student();
    Student& operator=(const Student& A);
    void clear();
    double results();
    friend ostream& operator<< (ostream& out, const Student& A);
    friend istream& operator>> (istream& in, const Student& A);
};
