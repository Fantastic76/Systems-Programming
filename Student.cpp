#include "Student.h"

static void checkScore(int value, const string& what) {
    if (value < Student::MIN_SCORE || value > Student::MAX_SCORE)
        throw invalid_argument(what + " must be between " + to_string(Student::MIN_SCORE) +
                               " and " + to_string(Student::MAX_SCORE) + ", got " + to_string(value));
}

Student::Student() : name("0"), surname("0"), exam(0) {}

Student::Student(string n, string s, vector<int> p, int e)
    : name(move(n)), surname(move(s)), points(move(p)), exam(e) {
    if (points.empty())
        throw invalid_argument("Student " + name + " " + surname + " has no homework points");
    for (int v : points) checkScore(v, "Homework score");
    checkScore(exam, "Exam score");
}

void Student::clear() {
    name.clear();
    surname.clear();
    points.clear();
    exam = 0;
}

double Student::getMedian() const {
    if (points.empty()) throw domain_error("Cannot compute median: no homework points");
    vector<int> sorted = points;               // copy: do not modify the student's data
    sort(sorted.begin(), sorted.end());
    size_t n = sorted.size();
    double median = (n % 2 != 0) ? sorted[n / 2]
                                 : (sorted[n / 2 - 1] + sorted[n / 2]) / 2.0;
    return median * 0.4 + exam * 0.6;
}

double Student::getAverage() const {
    if (points.empty()) throw domain_error("Cannot compute average: no homework points");
    double average = (double)accumulate(points.cbegin(), points.cend(), 0) / points.size();
    return average * 0.4 + exam * 0.6;
}

double Student::getFinalGrade(Method m) const {
    return (m == Method::Average) ? getAverage() : getMedian();
}

ostream& operator<<(ostream& out, const Student& A) {
    out << left << setw(15) << A.name << setw(15) << A.surname;
    return out;
}

istream& operator>>(istream& in, Student& A) {
    string name, surname;
    if (!(in >> name >> surname))              // normal end of file / no more records
        return in;

    vector<int> pts(Student::HOMEWORK_COUNT);
    for (int& p : pts)
        if (!(in >> p))
            throw invalid_argument("Incomplete or invalid homework data for " + name + " " + surname);

    int exam;
    if (!(in >> exam))
        throw invalid_argument("Missing or invalid exam score for " + name + " " + surname);

    A = Student(name, surname, pts, exam);     // constructor validates the ranges
    return in;
}
