#pragma once
#include "lib.h"

// How the final grade is calculated from homework results.
enum class Method { Average = 1, Median = 2 };

class Student {
private:
    string name, surname;
    Container<int> points;
    int exam;
    double average = 0, median = 0;   // final grades, computed once in the constructor

    void requireData() const;

public:
    static const int HOMEWORK_COUNT = 15;
    static const int MIN_SCORE = 0;
    static const int MAX_SCORE = 10;

    Student();
    // Throws std::invalid_argument if points are empty or any score is out of range.
    Student(string n, string s, Container<int> p, int e);

    void clear();

    const string& getName() const { return name; }
    const string& getSurname() const { return surname; }

    // All throw std::domain_error if the student has no homework points.
    double getAverage() const;
    double getMedian() const;
    double getFinalGrade(Method m) const;

    // operator>> throws std::invalid_argument on an incomplete/invalid record.
    friend ostream& operator<<(ostream& out, const Student& A);
    friend istream& operator>>(istream& in, Student& A);
};
