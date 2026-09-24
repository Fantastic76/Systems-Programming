#include "Student.h"
bool Alphabetical(Student A, Student B) {
    return A.getName() >= B.getName();
}
bool FinalNote(Student A, Student B) {
    return A.getFinalGrade() >= B.getFinalGrade();
}

void results(char i, Student& B) {
    if (i == '1') {
        B.average();
    }
    else {
        B.median();
    }
}
int main() {
    vector <Student> Class;
    char formula;
    while (true) {
        cout << "Would you like to use the average or the median to calculate the final grade?" << "\n";
        cout << "1: Average, 2: Median";
        cin >> formula;
        Student A;
        Student B(A);
        results(formula, B);
        Class.push_back(B);
        B.clear();
        cout << "Would you like to input another Student ? Y/N";
        string i; cin >> i;
        if (i == "n" || i == "N") break;
    }
    cout << "How would you to sort the student list?" << "\n";
    cout << "1: By name (Alphabetical), 2: By highest final note, 3: By lowest final point" << "\n";
    char sel;
    cin >> sel;
    switch (sel) {
    case '1':
        sort(Class.begin(), Class.end(), Alphabetical);
        break;
    case '2' :
        sort(Class.begin(), Class.end(), FinalNote);
        break;
        sort(Class.begin(), Class.end(), FinalNote);
    case '3' :
        break;
    default:
       cout << "No method was choosen, the class will not be sorted" << "\n";
       break;
    }
    for (Student i : Class) cout << i;
}
