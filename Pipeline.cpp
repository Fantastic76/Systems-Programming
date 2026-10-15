#include "Pipeline.h"
#include "Generator.h"
#include "Timer.h"

void generateAllFiles() {
    StudentGenerator gen;
    for (size_t n : FILE_SIZES) {
        string path = makeFileName("students", n);
        Timer t;
        gen.generateFile(path, n);
        cout << "Generated " << setw(10) << n << " records -> " << path
             << "  (" << fixed << setprecision(3) << t.elapsed() << " s)\n";
    }
}

void processFile(size_t count, Method m, SortOrder order) {
    const string inPath     = makeFileName("students", count);
    const string passedPath = makeFileName("passed", count);
    const string failedPath = makeFileName("failed", count);

    cout << "\n=== " << inPath << " ===\n" << fixed << setprecision(3);
    Timer total, t;

    Classroom passed;
    try {
        passed.loadFromFile(inPath);
    } catch (const runtime_error& e) {
        throw runtime_error(string(e.what()) + " (generate the files first)");
    }
    const size_t all = passed.size();
    cout << "Read file:           " << t.elapsed() << " s\n";

    t.reset();
    passed.sort(order, m);
    cout << "Sort:                " << t.elapsed() << " s\n";

    t.reset();
    Classroom failed = passed.extractFailed(m);      // 'passed' keeps students >= 5.0
    cout << "Divide into groups:  " << t.elapsed() << " s\n";

    t.reset();
    passed.saveToFile(passedPath, m);
    failed.saveToFile(failedPath, m);
    cout << "Write 2 files:       " << t.elapsed() << " s\n";

    cout << "Total:               " << total.elapsed() << " s\n"
         << "Students: " << all << "  passed: " << passed.size() << " (" << passedPath << ")"
         << "  failed: " << failed.size() << " (" << failedPath << ")\n";
}
