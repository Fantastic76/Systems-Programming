
#include "lib.h"

class Student {
private:
    string name, surname;
    vector <int> Points;
    int exam;
public:
    Student();
    Student(string n, string s, vector<int> P, int E);
    Student(const Student& B);
    ~Student();
    Student& operator=(const Student& A);
    void clear();
    friend ostream& operator<<(ostream& out, const Student& A);
    friend istream& operator>>(istream& in, Student& A);
    string getName();
    double getAverage();
    double getMedian();
    const double getFinalGrade(char i);
};
