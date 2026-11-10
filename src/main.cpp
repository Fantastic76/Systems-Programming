#include "Pipeline.h"
#include "Input.h"

int main() {
    try {
        while (true) {
            int choice = readChoice(
                "\n1: Generate the four student files (10 000 / 100 000 / 1 000 000 / 10 000 000)\n"
                "2: Process one file (choose container, strategy and implementation)\n"
                "3: Benchmark all containers, strategies and implementations\n"
                "0: Exit\n> ", 0, 3);
            if (choice == 0) break;

            try {
                if (choice == 1) {
                    generateAllFiles();
                    continue;
                }

                int idx = readChoice("Which file?\n1: 10 000, 2: 100 000, 3: 1 000 000, 4: 10 000 000"
                                     + string(choice == 3 ? ", 5: all four" : "") + "\n> ",
                                     1, choice == 3 ? 5 : 4);

                ContainerKind kind = ContainerKind::Vector;
                Strategy strategy = Strategy::CopyToTwo;
                Impl impl = Impl::Manual;
                if (choice == 2) {
                    kind = static_cast<ContainerKind>(readChoice("Container: 1: vector, 2: list, 3: deque\n> ", 1, 3));
                    strategy = static_cast<Strategy>(readChoice(
                        "Strategy: 1: copy into two new containers (passed + failed),\n"
                        "          2: move failed into one new container and erase them from the original\n> ", 1, 2));
                    impl = static_cast<Impl>(readChoice("Implementation: 1: manual loops, 2: <algorithm> functions\n> ", 1, 2));
                }

                Method method = static_cast<Method>(readChoice(
                    "Final grade by: 1: Average, 2: Median\n> ", 1, 2));
                SortOrder order = static_cast<SortOrder>(readChoice(
                    "Sort by: 1: Name, 2: Highest final grade, 3: Lowest final grade\n> ", 1, 3));

                if (choice == 2) {
                    processFile(FILE_SIZES[idx - 1], kind, strategy, impl, method, order);
                } else if (idx == 5) {
                    for (size_t n : FILE_SIZES) benchmarkFile(n, method, order);
                } else {
                    benchmarkFile(FILE_SIZES[idx - 1], method, order);
                }
            }
            catch (const invalid_argument& e) { cerr << "Data error: " << e.what() << "\n"; }
            catch (const bad_alloc&)          { cerr << "Error: out of memory\n"; }
            catch (const runtime_error& e)    { cerr << "Error: " << e.what() << "\n"; }
            catch (const exception& e)        { cerr << "Error: " << e.what() << "\n"; }
        }
    }
    catch (const exception& e) {
        cerr << "Fatal error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
