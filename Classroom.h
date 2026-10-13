#pragma once
#include "Student.h"

enum class SortOrder { Alphabetical = 1, HighestGrade = 2, LowestGrade = 3 };

// Holds a collection of students and knows how to load, sort, print and save them.
class Classroom {
private:
    vector<Student> students;

public:
    size_t size() const { return students.size(); }

    // Throws std::runtime_error if the file cannot be opened or contains no students;
    // std::invalid_argument for malformed records.
    void loadFromFile(const string& path);

    void sort(SortOrder order, Method m);

    void print(ostream& out, Method m) const;

    // Throws std::runtime_error if the file cannot be written.
    void saveToFile(const string& path, Method m) const;
};
