#include "Classroom.h"
#include "Input.h"

int main() {
    try {
        Classroom group;
        group.loadFromFile("Students.txt");

        Method method = static_cast<Method>(readChoice(
            "Would you like to use the average or the median to calculate the final grade?\n"
            "1: Average, 2: Median\n> ", 1, 2));

        SortOrder order = static_cast<SortOrder>(readChoice(
            "How would you like to sort the student list?\n"
            "1: By name (alphabetical), 2: By highest final grade, 3: By lowest final grade\n> ", 1, 3));

        group.sort(order, method);
        group.print(cout, method);
        group.saveToFile("Answer.txt", method);
        cout << "\nResults saved to Answer.txt\n";
    }
    catch (const invalid_argument& e) {
        cerr << "Data error: " << e.what() << "\n";
        return 2;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
