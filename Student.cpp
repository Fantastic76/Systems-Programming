
#include "Student.h"
Student::Student(){}
Student::Student(string n, string s, vector<int> P, int E) {
    name = n;
    surname = s;
    Points = P;
    exam = E;
    final = results();
}

ostream& operator<< (ostream& out, const Student& A) {
  cout << A.name << "|" << A.surname << "|" << A.final << "\n";
  return out;
}
istream& operator>> (istream& in, Student& A) {
    string name, surname;
    vector <int> Points;
    int exam;
    cout << "Input name: "; cin >> name;
    cout << "Input surname: "; cin >> surname;
    int n;
    while (true) {
        cin >> n;
        Points.push_back(n);
        cout << "Want to input another point ? Y/N";
        string i; cin >> i;
        if (i == "n" || i == "N") break;
    }
    cout << "Input exam: ";
    cin >> exam;
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
double Student :: results() {
    int average;
    average = accumulate(Points.cbegin(), Points.cend(), 0) / Points.size();
    return (average * 0.4 + exam * 0.6);
}
