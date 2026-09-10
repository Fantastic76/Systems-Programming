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
    void clear();
    double results();
};