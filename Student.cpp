
#include "Student.h"
Student::Student() {
    name = "0";
    surname = "0";
    exam = 0;
}
Student::Student(string n, string s, vector<int> P, int E) {
    name = n;
    surname = s;
    Points = P;
    exam = E;
}
Student::Student(const Student& A) {
       name = A.name;
       surname = A.surname;
       Points = A.Points;
       exam = A.exam;
}

ostream& operator<< (ostream& out, const Student& A) {
  out << A.name << "|" << A.surname << "|";
  return out;
}

istream& operator>>(istream& in, Student& A)
{
    string name;
    string surname;
    vector<int> points(15);
    int exam;

    if (in >> name >> surname)
    {
        for (int i = 0; i < 15; i++)
        {
            if (!(in >> points[i]))
                return in;
        }

        if (!(in >> exam))
            return in;

        A = Student(name, surname, points, exam);
    }

    return in;
}

Student :: ~Student() {
    name.clear();
    surname.clear();
    Points.clear();
    exam = 0;
}
Student& Student :: operator=(const Student &A) {
    if (this != &A) {
        name = A.name;
        surname = A.surname;
        Points = A.Points;
        exam = A.exam;
    }
    return *this;
}
void Student :: clear() {
    name.clear();
    surname.clear();
    Points.clear();
    exam = 0;
}
string Student:: getName() { return name; }
double Student::getMedian() {
    double median;
    sort(Points.begin(), Points.end());
    if (Points.size() % 2 != 0) median = (double)Points[Points.size() / 2];
    else median = (double)(Points[(Points.size() - 1) / 2] + Points[Points.size() / 2]) / 2.0;
    return (median * 0.4 + exam * 0.6);
}
double Student::getAverage() {
    double average;
    average = (double)accumulate(Points.cbegin(), Points.cend(), 0) / Points.size();
    return (average * 0.4 + exam * 0.6);
}
const double Student::getFinalGrade(char i) {
    if (i == '1') {
        return getAverage();
    }
    else {
        return getMedian();
    }
}