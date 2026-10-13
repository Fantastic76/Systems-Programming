#include "Classroom.h"

void Classroom::loadFromFile(const string& path) {
    ifstream file(path);
    if (!file) throw runtime_error("Could not open file: " + path);

    string header;
    getline(file, header);                     // skip the header line

    students.clear();
    Student s;
    while (file >> s) students.push_back(s);

    if (students.empty()) throw runtime_error("No students found in " + path);
}

void Classroom::sort(SortOrder order, Method m) {
    switch (order) {
    case SortOrder::Alphabetical:
        std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
            if (a.getName() != b.getName()) return a.getName() < b.getName();
            return a.getSurname() < b.getSurname();
        });
        break;
    case SortOrder::HighestGrade:
        std::sort(students.begin(), students.end(), [m](const Student& a, const Student& b) {
            return a.getFinalGrade(m) > b.getFinalGrade(m);
        });
        break;
    case SortOrder::LowestGrade:
        std::sort(students.begin(), students.end(), [m](const Student& a, const Student& b) {
            return a.getFinalGrade(m) < b.getFinalGrade(m);
        });
        break;
    }
}

void Classroom::print(ostream& out, Method m) const {
    out << fixed << setprecision(2) << left
        << setw(15) << "Name"
        << setw(15) << "Surname"
        << (m == Method::Average ? "Final (Avg.)" : "Final (Med.)") << "\n"
        << string(45, '-') << "\n";
    for (const Student& s : students)
        out << s << s.getFinalGrade(m) << "\n";
}

void Classroom::saveToFile(const string& path, Method m) const {
    ofstream out(path);
    if (!out) throw runtime_error("Could not open file for writing: " + path);
    print(out, m);
    if (!out) throw runtime_error("Error while writing to file: " + path);
}
