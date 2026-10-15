#pragma once
#include "Student.h"

enum class SortOrder { Alphabetical = 1, HighestGrade = 2, LowestGrade = 3 };

// Holds a collection of students and knows how to load, sort, split, print and save them.
class Classroom {
private:
    Container<Student> students;

public:
    static constexpr double PASS_GRADE = 5.0;   // final < 5.0 -> "failed", >= 5.0 -> "passed"

    size_t size() const { return students.size(); }

    // Throws std::runtime_error if the file cannot be opened or contains no students;
    // std::invalid_argument for malformed records.
    void loadFromFile(const string& path);

    void sort(SortOrder order, Method m);

    // Moves every student with a final grade < PASS_GRADE into the returned Classroom.
    // Students with a grade >= PASS_GRADE stay in this Classroom.
    // The relative (sorted) order of students is preserved in both containers.
    Classroom extractFailed(Method m);

    void print(ostream& out, Method m) const;

    // Throws std::runtime_error if the file cannot be written.
    void saveToFile(const string& path, Method m) const;
};
