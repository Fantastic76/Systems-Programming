#include "Pipeline.h"
#include "Input.h"

int main() {
    try {
        while (true) {
            int choice = readChoice(
                "\n1: Generate the four student files (10 000 / 100 000 / 1 000 000 / 10 000 000)\n"
                "2: Process one file (sort + divide into passed/failed)\n"
                "3: Process all four files\n"
                "0: Exit\n> ", 0, 3);
            if (choice == 0) break;

            try {
                if (choice == 1) {
                    generateAllFiles();
                    continue;
                }

                size_t count = 0;
                if (choice == 2) {
                    int idx = readChoice("Which file?\n1: 10 000, 2: 100 000, 3: 1 000 000, 4: 10 000 000\n> ", 1, 4);
                    count = *next(FILE_SIZES.begin(), idx - 1);
                }

                Method method = static_cast<Method>(readChoice(
                    "Final grade by: 1: Average, 2: Median\n> ", 1, 2));
                SortOrder order = static_cast<SortOrder>(readChoice(
                    "Sort by: 1: Name, 2: Highest final grade, 3: Lowest final grade\n> ", 1, 3));

                if (choice == 2) processFile(count, method, order);
                else for (size_t n : FILE_SIZES) processFile(n, method, order);
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
