#include "Student.h"
static bool Alphabetical(Student A, Student B) {
    return A.getName() > B.getName();
}
int main() {
    vector <Student> Class;
    ifstream file("Students.txt");
    if (!file)
    {
        cout << "Error: Could not open Students.txt" << endl;
        return 1;
    }
    char formula;
    string header;
    getline(file, header);
    cout << "Would you like to use the average or the median to calculate the final grade?" << "\n";
    cout << "1: Average, 2: Median";
    cin >> formula;
    Student student;
    while (file >> student)
    {
        Class.push_back(student); 
    }
    file.close();
   
    cout << "How would you to sort the student list?" << "\n";
    cout << "1: By name (Alphabetical), 2: By highest final note, 3: By lowest final point" << "\n";
    char sel;
    cin >> sel;
    switch (sel) {
    case '1':
        sort(Class.begin(), Class.end(), Alphabetical);
        break;
    case '2':
        sort(Class.begin(), Class.end(),
            [formula](Student& A,Student& B)
            {
                return A.getFinalGrade(formula) > B.getFinalGrade(formula);
            });
        break;

    case '3':
        sort(Class.begin(), Class.end(),
            [formula](Student& A, Student& B)
            {
                return A.getFinalGrade(formula) < B.getFinalGrade(formula);
            });
        break;
    default:
       cout << "No method was choosen, the class will not be sorted" << "\n";
       break;
    }
    cout << fixed << setprecision(2);

    cout << left
        << setw(15) << "Name"
        << setw(15) << "Surname"
        << setw(15) << "Final (Avg.)"
        << setw(15) << "Final (Med.)"
        << endl;

    cout << "------------------------------------------------------------"
        << endl;
    for (Student i : Class) cout << i << i.getFinalGrade(formula) << endl;
}
