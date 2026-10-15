#include "Generator.h"
#include "Student.h"

string makeFileName(const string& prefix, size_t count) {
    return prefix + "_" + to_string(count) + ".txt";
}

StudentGenerator::StudentGenerator() : rng(random_device{}()) {}

void StudentGenerator::generateFile(const string& path, size_t count) {
    if (count == 0) throw invalid_argument("Number of records must be greater than 0");

    ofstream out(path);
    if (!out) throw runtime_error("Could not open file for writing: " + path);

    string buf;
    buf.reserve((1 << 20) + 256);

    buf += "Name Surname";
    for (int i = 1; i <= Student::HOMEWORK_COUNT; i++) buf += " HW" + to_string(i);
    buf += " Exam\n";

    for (size_t i = 1; i <= count; i++) {
        buf += "Name" + to_string(i) + " Surname" + to_string(i);
        for (int j = 0; j < Student::HOMEWORK_COUNT; j++) buf += ' ' + to_string(score(rng));
        buf += ' ' + to_string(score(rng));    // exam
        buf += '\n';

        if (buf.size() >= (1 << 20)) {         // write in ~1 MB chunks: much faster than per-line output
            out << buf;
            buf.clear();
        }
    }
    out << buf;
    out.flush();
    if (!out) throw runtime_error("Error while writing to file: " + path);
}
