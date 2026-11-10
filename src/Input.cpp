#include "Input.h"

int readChoice(const string& prompt, int min, int max) {
    while (true) {
        cout << prompt;
        int value;
        if (cin >> value) {
            if (value >= min && value <= max) return value;
            cout << "Please enter a number between " << min << " and " << max << ".\n";
        } else {
            if (cin.eof()) throw runtime_error("Input stream closed");
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input, please enter a number.\n";
        }
    }
}
