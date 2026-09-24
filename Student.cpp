
#include "Student.h"
Student::Student() {
    cout << "Input name: "; cin >> name;
    cout << "Input surname: "; cin >> surname;
    cout << "Input homework points: ";
    int n;
    while (true) {
        cin >> n;
        Points.push_back(n);
        cout << "Would you like to input another point ? Y/N";
        string i; cin >> i;
        if (i == "n" || i == "N") break;
    }
    cout << "Input exam: ";
    cin >> exam;
    final = 0;
}
Student::Student(string n, string s, vector<int> P, int E) {
    name = n;
    surname = s;
    Points = P;
    exam = E;
    final = 0;
}
Student::Student(const Student& A) {
       name = A.name;
       surname = A.surname;
       Points = A.Points;
       exam = A.exam;
       final = 0;
}

ostream& operator<< (ostream& out, const Student& A) {
  cout << A.name << "|" << A.surname << "|" << A.final << "\n";
  return out;
}
istream& operator>> (istream& in, Student& A) {
    string name, surname;
    vector <int> Points;
    int exam;
    cout << "Input name: "; in >> name;
    cout << "Input surname: "; in >> surname;
    cout << "Input homework points: ";
    int n;
    while (true) {
        in >> n;
        Points.push_back(n);
        cout << "Would you like to input another point ? Y/N";
        string i; in >> i;
        if (i == "n" || i == "N") break;
    }
    cout << "Input exam: ";
    in >> exam;
    A = Student(name, surname, Points, exam);
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
void Student :: average() {
    double average;
    average = (double) accumulate(Points.cbegin(), Points.cend(), 0) / Points.size();
    final = (average * 0.4 + exam * 0.6);
}
void Student::median() {
    double median;
    sort(Points.begin(), Points.end());
    if (Points.size() % 2 != 0) median = (double)Points[Points.size() / 2];
    else median = (double)(Points[(Points.size() - 1) / 2] + Points[Points.size() / 2]) / 2.0;
    final = (median * 0.4 + exam * 0.6);
}


string Student:: getName() { return name; }
double Student::getFinalGrade() { return final;}