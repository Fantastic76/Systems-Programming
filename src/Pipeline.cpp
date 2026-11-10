#include "Pipeline.h"
#include "Generator.h"
#include "Timer.h"
#include "Memory.h"

namespace {

const double MB = 1024.0 * 1024.0;

// The naive "erase one by one" strategy 2 is O(n^2) for vector and deque; above this size
// the benchmark skips it instead of running for hours.
const size_t NAIVE_ERASE_LIMIT = 100000;

const char* name(ContainerKind k) {
    return k == ContainerKind::Vector ? "vector" : k == ContainerKind::List ? "list" : "deque";
}
const char* name(Strategy s) { return s == Strategy::CopyToTwo ? "1 (copy to 2)" : "2 (move to 1)"; }
const char* name(Impl i)     { return i == Impl::Manual ? "manual" : "algorithm"; }

struct Result {
    double seconds = 0;
    double peakExtraMB = 0;    // highest extra heap use during the division
    double liveExtraMB = 0;    // extra heap use that remains after the division
    size_t passed = 0, failed = 0;
};

// Divides 'room' with the given strategy and measures time and memory. Strategy 1 leaves
// 'room' untouched; strategy 2 leaves only the passed students in it. If 'keep' is not null,
// the two resulting groups are handed back (for writing to files).
template <class C>
Result divide(Classroom<C>& room, Strategy st, Impl impl, Method m,
              Classroom<C>* keepPassed = nullptr, Classroom<C>* keepFailed = nullptr) {
    Result r;
    const size_t base = memtrack::current();
    memtrack::resetPeak();
    Timer t;

    if (st == Strategy::CopyToTwo) {
        auto groups = room.splitCopy(m, impl);
        r.seconds = t.elapsed();
        r.peakExtraMB = (memtrack::peak() - base) / MB;
        r.liveExtraMB = (memtrack::current() - base) / MB;
        r.passed = groups.first.size();
        r.failed = groups.second.size();
        if (keepPassed) { *keepPassed = move(groups.first); *keepFailed = move(groups.second); }
    } else {
        Classroom<C> failed = room.extractFailed(m, impl);
        r.seconds = t.elapsed();
        r.peakExtraMB = (memtrack::peak() - base) / MB;
        r.liveExtraMB = (memtrack::current() - base) / MB;
        r.passed = room.size();
        r.failed = failed.size();
        if (keepPassed) { *keepPassed = move(room); *keepFailed = move(failed); }
    }
    return r;
}

template <class C>
void processFileT(size_t count, ContainerKind kind, Strategy st, Impl impl, Method m, SortOrder order) {
    const string inPath     = makeFileName("students", count);
    const string passedPath = makeFileName("passed", count);
    const string failedPath = makeFileName("failed", count);

    cout << "\n=== " << inPath << "  [" << name(kind) << ", strategy " << name(st)
         << ", " << name(impl) << "] ===\n" << fixed << setprecision(3);
    Timer total, t;

    Classroom<C> room;
    try {
        room.loadFromFile(inPath);
    } catch (const runtime_error& e) {
        throw runtime_error(string(e.what()) + " (generate the files first)");
    }
    const size_t all = room.size();
    cout << "Read file:           " << t.elapsed() << " s\n";

    t.reset();
    room.sort(order, m);
    cout << "Sort:                " << t.elapsed() << " s\n";

    const double baseMB = memtrack::current() / MB;
    Classroom<C> passed, failed;
    Result r = divide(room, st, impl, m, &passed, &failed);
    cout << "Divide into groups:  " << r.seconds << " s\n"
         << setprecision(1)
         << "Memory:              students " << baseMB << " MB, +" << r.peakExtraMB
         << " MB peak and +" << r.liveExtraMB << " MB left after dividing\n" << setprecision(3);

    t.reset();
    passed.saveToFile(passedPath, m);
    failed.saveToFile(failedPath, m);
    cout << "Write 2 files:       " << t.elapsed() << " s\n";

    cout << "Total:               " << total.elapsed() << " s\n"
         << "Students: " << all << "  passed: " << r.passed << " (" << passedPath << ")"
         << "  failed: " << r.failed << " (" << failedPath << ")\n";
}

struct Row { ContainerKind kind; Strategy st; Impl impl; bool skipped; Result r; };

template <class C>
void benchmarkT(size_t count, ContainerKind kind, Method m, SortOrder order, vector<Row>& rows) {
    Classroom<C> base;
    Timer t;
    base.loadFromFile(makeFileName("students", count));
    cout << "  " << name(kind) << ": read " << t.elapsed() << " s";
    t.reset();
    base.sort(order, m);
    cout << ", sort " << t.elapsed() << " s\n" << flush;

    for (Impl impl : {Impl::Manual, Impl::Algorithm}) {
        rows.push_back({kind, Strategy::CopyToTwo, impl, false,
                        divide(base, Strategy::CopyToTwo, impl, m)});

        bool skip = impl == Impl::Manual && kind != ContainerKind::List && count > NAIVE_ERASE_LIMIT;
        if (skip) {
            rows.push_back({kind, Strategy::MoveToOne, impl, true, {}});
            continue;
        }
        Classroom<C> copy = base;               // strategy 2 destroys its input, so use a copy
        rows.push_back({kind, Strategy::MoveToOne, impl, false,
                        divide(copy, Strategy::MoveToOne, impl, m)});
    }
}

} // namespace

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

void processFile(size_t count, ContainerKind kind, Strategy st, Impl impl, Method m, SortOrder order) {
    switch (kind) {
    case ContainerKind::Vector: processFileT<vector<Student>>(count, kind, st, impl, m, order); break;
    case ContainerKind::List:   processFileT<list<Student>>  (count, kind, st, impl, m, order); break;
    case ContainerKind::Deque:  processFileT<deque<Student>> (count, kind, st, impl, m, order); break;
    }
}

void benchmarkFile(size_t count, Method m, SortOrder order) {
    cout << "\n=== Benchmark: students_" << count << ".txt ===\n" << fixed << setprecision(3);
    vector<Row> rows;
    benchmarkT<vector<Student>>(count, ContainerKind::Vector, m, order, rows);
    benchmarkT<list<Student>>  (count, ContainerKind::List,   m, order, rows);
    benchmarkT<deque<Student>> (count, ContainerKind::Deque,  m, order, rows);

    cout << "\n" << left << setw(8) << "Cont." << setw(15) << "Strategy" << setw(11) << "Impl."
         << right << setw(11) << "Divide [s]" << setw(13) << "+Peak [MB]" << setw(13) << "+Left [MB]"
         << setw(10) << "Passed" << setw(10) << "Failed" << "\n" << string(91, '-') << "\n";
    for (const Row& row : rows) {
        cout << left << setw(8) << name(row.kind) << setw(15) << name(row.st) << setw(11) << name(row.impl);
        if (row.skipped) {
            cout << right << "   skipped (O(n^2) erase, n > " << NAIVE_ERASE_LIMIT << ")\n";
            continue;
        }
        cout << right << setw(11) << setprecision(4) << row.r.seconds
             << setw(13) << setprecision(1) << row.r.peakExtraMB
             << setw(13) << row.r.liveExtraMB
             << setw(10) << row.r.passed << setw(10) << row.r.failed << "\n";
    }
}
