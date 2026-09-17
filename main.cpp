#include "Student.h"

int main() {
    vector <Student> Class;
    while (true) {
        Student n;
        Class.push_back(n);
        n.clear();
        cout << "Want to input another Student ? Y/N";
        string i; cin >> i;
        if (i == "n" || i == "N") break;
    }
    for (Student i : Class) cout << i;
}
