# Systems-Programming – Student sorting and grouping

A C++17 console program that reads students (name, surname, 15 homework scores, exam score), calculates the final
grade (average or median), sorts the students and divides them into **passed** (final ≥ 5.0) and **failed**
(final < 5.0). The task of this release is to compare how the program behaves with different **containers**
(`std::vector`, `std::list`, `std::deque`), **division strategies** and **implementations** (hand-written loops vs
`<algorithm>`).

## Releases

| Release | What it contains |
|---|---|
| **v0.25** | Task 2 version. One container type chosen at compile time (`std::deque`, or `std::list` with `-DUSE_LIST`). Students are split by `Classroom::extractFailed`, a single pass that moves failed students out and erases them from the original (one `erase` at the end). Files for 10 000 / 100 000 / 1 000 000 / 10 000 000 students are generated and processed. |
| **v0.3-strategy1** | Container chosen at run time (vector / list / deque). Strategy 1: students are **copied** into two new containers `passed` and `failed`; the original container keeps everything. Added time and memory measurement (`Memory.cpp` counts bytes requested from `operator new`). |
| **v0.3-strategy2** | Same, but Strategy 2: failed students are **moved** into one new container and **erased** from the original, which is then shrunk. Manual version erases one by one; the refactored version uses `std::stable_partition`. |
| **v1.0 (this repository)** | Both strategies in one program with a menu. Every combination of container × strategy × implementation (manual / `<algorithm>`) can be run on one file or benchmarked in a table. Includes `Makefile` (Unix) and `CMakeLists.txt` (any OS). |

### `<algorithm>` functions used in v1.0

| Function | Where |
|---|---|
| `std::remove_copy_if` | Strategy 1: one call copies the passed students, one copies the failed ones |
| `std::stable_partition` | Strategy 2: passed students first, failed ones after the split point, order preserved |
| `std::move` (algorithm) + `erase` | Strategy 2: failed tail is moved into the new container, then removed with one `erase` |
| `std::find_if` | `Student`: finds the first invalid homework score |
| `std::sort` / `list::sort` | sorting (list has no random access, so it uses its member `sort`) |
| `std::accumulate` | average of the homework scores |

`std::find`, `std::search`, `std::copy`, `std::remove`, `std::remove_if`, `std::remove_copy`, `std::transform` and
`std::partition` were considered but not needed: `remove_if`/`partition` would either be slower or break the sorted
order of the groups, and the other functions have no step in this program they naturally replace.

## Usage guide

### 1. Requirements
A C++17 compiler (g++ ≥ 7, clang ≥ 5, MSVC 2017+). About 3 GB of free RAM is needed for the 1 000 000 file in
strategy 1, and much more for 10 000 000 students.

### 2. Build with Make (Linux, macOS, WSL)
```bash
git clone <https://github.com/Fantastic76/Systems-Programming.git>
cd <repository-folder>
make            # builds ./studentsort  (objects go to build/)
```
`make run` builds and starts the program, `make clean` removes the build output.

### 3. Build with CMake (any OS)
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```
The executable is `build/studentsort` (Linux/macOS), `build\Release\studentsort.exe` (Visual Studio) or
`build\studentsort.exe` (MinGW/Ninja). Always use a Release build, otherwise the measured times are meaningless.

### 4. Run
Start the program from the folder where the data files should be created (the files are read from and written to the
current directory):
```bash
./studentsort
```
Main menu:

| Choice | Action |
|---|---|
| `1` | Generate `students_10000.txt`, `students_100000.txt`, `students_1000000.txt`, `students_10000000.txt` (do this first; the 10 000 000 file is ~600 MB) |
| `2` | Process one file: choose file → container → strategy → implementation → final grade method → sort order. Writes `passed_<N>.txt` and `failed_<N>.txt` and prints time and memory of every step |
| `3` | Benchmark: choose file (or all four) → grade method → sort order. Runs every container × strategy × implementation and prints a comparison table (no files are written) |
| `0` | Exit |

Typical session: `1` (generate) → `3` → `3` (1 000 000 students) → `1` (average) → `1` (sort by name).

Input file format: a header line, then one student per line: `Name Surname hw1 … hw15 exam`, scores 0–10.

## Results

Measured on one core, g++ 13 `-O2`, final grade = average, sorted by name, one run each (expect some noise).
Divide time in seconds; "left" = extra memory still allocated after the division.

| n | container | S1 manual | S1 algorithm | S2 manual | S2 algorithm |
|---|---|---|---|---|---|
| 100 000 | vector | 0.0167 | 0.0142 | 17.41 | 0.0088 |
| 100 000 | list | 0.0123 | 0.0153 | **0.0052** | 0.0245 |
| 100 000 | deque | 0.0067 | 0.0107 | 8.16 | 0.0054 |
| 1 000 000 | vector | 0.188 | 0.203 | skipped | 0.192 |
| 1 000 000 | list | 0.185 | 0.344 | 0.126 | 0.502 |
| 1 000 000 | deque | **0.087** | 0.120 | skipped | 0.124 |

Memory at 1 000 000 students: strategy 1 leaves +168 MB (deque) … +225 MB (vector) allocated; strategy 2 leaves
0 MB (list), 1.2 MB (deque), 11.7 MB (vector).
The 10 000 000 file was not benchmarked (not enough RAM on the test machine).

### Comments

* **Strategy 1 is memory-inefficient – confirmed.** Every student exists twice afterwards, so the extra memory is
  about as large as the original container (≈ 170–225 MB at 1 000 000 students). Strategy 2 leaves almost nothing.
* **Strategy 1: `deque` is the fastest container** (about 2× faster than vector and list). Copying only needs
  `push_back`; deque grows in blocks without moving old elements and keeps good cache locality, vector has to
  reallocate and move, list allocates one node per student.
* **Strategy 2 with one-by-one erasing is "painful" for vector and deque:** every `erase` shifts the rest of the
  container, O(n²) overall – 17.4 s (vector) and 8.2 s (deque) already for 100 000 students, so these runs are
  skipped above 100 000. `list` erases in O(1) and is by far the best container for this naive version.
* **The algorithm version fixes it:** `stable_partition` + one `erase` makes vector and deque
  roughly 1000–2000× faster at 100 000 students (17.4 s → 0.009 s, 8.2 s → 0.005 s) and the result keeps the order.
* **For `list`, algorithms are slower than hand-written code** (S2: 0.126 s manual vs 0.50 s algorithm). A list can
  unlink nodes without moving any data, but `stable_partition` and `remove_copy_if` work through element moves/copies
  and temporary buffers. The same reason explains why `remove_copy_if` is slower for list in strategy 1 (the predicate
  also runs twice per student).
* **Overall:** the fastest combination for the whole task is strategy 2 on `list` (manual erase) or on `deque` with
  `stable_partition`; the best strategy-1 result is `deque`. When memory matters, strategy 2 wins either way.
  Sorting is a separate cost: `list` sorts fastest (0.16 s for 1 000 000), vector 0.42 s, deque 0.85 s.

## Project structure
```
src/              .cpp files (main, Pipeline, Student, Generator, Input, Memory)
include/          .h files (Classroom.h = container/strategy logic, Student.h, Timer.h, ...)
Makefile          Unix build
CMakeLists.txt    cross-platform build
```

## License
See `LICENSE`.
