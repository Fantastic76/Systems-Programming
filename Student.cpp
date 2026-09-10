
#include "Student.h"


Student::Student() {
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
}
Student::Student(string n, string s, vector<int> P, int E) {
    name = n;
    surname = s;
    Points = P;
    exam = E;
}
void Student :: print() {
    cout << name << "|" << surname << "|";
    for (int i : Points) cout << i << "|";
    cout << exam << "\n";
}

Student :: ~Student() {
    name.clear();
    surname.clear();
    Points.clear();
    exam = 0;
}
void Student :: clear() {
    name.clear();
    surname.clear();
    Points.clear();
    exam = 0;
}
double Student :: results() {
    return 0;
}