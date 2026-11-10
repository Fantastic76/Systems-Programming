#pragma once
#include "lib.h"

// Builds file names like "students_10000.txt", "failed_10000.txt".
string makeFileName(const string& prefix, size_t count);

// Creates student list files with random marks and names "Name1 Surname1", "Name2 Surname2", ...
class StudentGenerator {
private:
    mt19937 rng;
    uniform_int_distribution<int> score{1, 10};

public:
    StudentGenerator();

    // Throws std::invalid_argument if count == 0, std::runtime_error on file errors.
    void generateFile(const string& path, size_t count);
};
