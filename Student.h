#pragma once
#include "lib.h"

class Student {
    string name, surname;
    vector <int> Points;
    int exam;
public:
    Student();
    Student(string n, string s, vector<int> P, int E);
    void print();
    ~Student();
    Student& Student operator=(const Student &A)
    void clear();
    double results();
    friend ostream& operator<< (ostream& out, const Student& A);
    friend istream& operator>> (istream& in, const Student& A);
};
