#pragma once
#include "Student.h"

enum class SortOrder { Alphabetical = 1, HighestGrade = 2, LowestGrade = 3 };

// Strategy 1: copy students into two NEW containers (original stays intact).
// Strategy 2: move failed students into one new container and erase them from the original.
enum class Strategy { CopyToTwo = 1, MoveToOne = 2 };

// Manual: hand-written loops. Algorithm: the same job done with <algorithm> functions.
enum class Impl { Manual = 1, Algorithm = 2 };

// std::sort needs random access iterators, list has its own member sort().
template <class C, class Cmp>
void sortContainer(C& c, Cmp cmp) {
    using Cat = typename iterator_traits<typename C::iterator>::iterator_category;
    if constexpr (is_base_of_v<random_access_iterator_tag, Cat>) std::sort(c.begin(), c.end(), cmp);
    else c.sort(cmp);
}

// vector and deque can give memory back; list has no shrink_to_fit (nothing to give back).
template <class C> auto shrinkToFit(C& c, int) -> decltype(c.shrink_to_fit(), void()) { c.shrink_to_fit(); }
template <class C> void shrinkToFit(C&, long) {}

// C is std::vector<Student>, std::list<Student> or std::deque<Student>.
template <class C>
class Classroom {
private:
    C students;

    static bool isFailed(const Student& s, Method m) { return s.getFinalGrade(m) < PASS_GRADE; }

public:
    static constexpr double PASS_GRADE = 5.0;   // final < 5.0 -> "failed", >= 5.0 -> "passed"

    size_t size() const { return students.size(); }

    // Throws std::runtime_error if the file cannot be opened or contains no students;
    // std::invalid_argument for malformed records.
    void loadFromFile(const string& path) {
        ifstream file(path);
        if (!file) throw runtime_error("Could not open file: " + path);

        string header;
        getline(file, header);                 // skip the header line

        students.clear();
        Student s;
        while (file >> s) students.push_back(move(s));

        if (students.empty()) throw runtime_error("No students found in " + path);
    }

    void sort(SortOrder order, Method m) {
        switch (order) {
        case SortOrder::Alphabetical:
            sortContainer(students, [](const Student& a, const Student& b) {
                if (a.getName() != b.getName()) return a.getName() < b.getName();
                return a.getSurname() < b.getSurname();
            });
            break;
        case SortOrder::HighestGrade:
            sortContainer(students, [m](const Student& a, const Student& b) {
                return a.getFinalGrade(m) > b.getFinalGrade(m);
            });
            break;
        case SortOrder::LowestGrade:
            sortContainer(students, [m](const Student& a, const Student& b) {
                return a.getFinalGrade(m) < b.getFinalGrade(m);
            });
            break;
        }
    }

    // ---- Strategy 1 -------------------------------------------------------------------
    // Returns {passed, failed}; this Classroom is not modified (every student exists twice).
    pair<Classroom, Classroom> splitCopy(Method m, Impl impl) const {
        Classroom passed, failed;
        if (impl == Impl::Manual) {
            for (const Student& s : students)
                (isFailed(s, m) ? failed : passed).students.push_back(s);
        } else {
            // remove_copy_if copies everything EXCEPT the elements matching the predicate
            remove_copy_if(students.begin(), students.end(), back_inserter(passed.students),
                           [m](const Student& s) { return isFailed(s, m); });
            remove_copy_if(students.begin(), students.end(), back_inserter(failed.students),
                           [m](const Student& s) { return !isFailed(s, m); });
        }
        return {move(passed), move(failed)};
    }

    // ---- Strategy 2 -------------------------------------------------------------------
    // Moves every student with grade < PASS_GRADE into the returned Classroom and erases
    // them from this one, which then holds only passed students (and is shrunk to fit).
    Classroom extractFailed(Method m, Impl impl) {
        Classroom failed;
        if (impl == Impl::Manual) {
            // Straightforward version: erase each failed student as soon as it is found.
            // O(1) per erase for list, O(n) per erase for vector/deque.
            for (auto it = students.begin(); it != students.end();) {
                if (isFailed(*it, m)) {
                    failed.students.push_back(move(*it));
                    it = students.erase(it);
                } else {
                    ++it;
                }
            }
        } else {
            // passed students first, failed ones after 'split', relative order kept in both parts
            auto split = stable_partition(students.begin(), students.end(),
                                          [m](const Student& s) { return !isFailed(s, m); });
            move(split, students.end(), back_inserter(failed.students));   // std::move algorithm
            students.erase(split, students.end());                         // one erase call
        }
        shrinkToFit(students, 0);
        return failed;
    }

    void print(ostream& out, Method m) const {
        out << fixed << setprecision(2) << left
            << setw(15) << "Name"
            << setw(15) << "Surname"
            << (m == Method::Average ? "Final (Avg.)" : "Final (Med.)") << "\n"
            << string(45, '-') << "\n";
        for (const Student& s : students)
            out << s << s.getFinalGrade(m) << "\n";
    }

    // Throws std::runtime_error if the file cannot be written.
    void saveToFile(const string& path, Method m) const {
        ofstream out(path);
        if (!out) throw runtime_error("Could not open file for writing: " + path);
        print(out, m);
        out.flush();
        if (!out) throw runtime_error("Error while writing to file: " + path);
    }
};
