#include "Student.h"
static bool Alphabetical(Student A, Student B) {
    return A.getName() > B.getName();
}
int main() {
    vector <Student> Class;
    char source;
    cout << "Where should the students come from?" << "\n";
    cout << "1: Read from Students.txt, 2: Generate random students" << "\n";
    cin >> source;

    if (source == '2') {
        int count;
        cout << "How many students to generate? ";
        cin >> count;
        for (int i = 1; i <= count; i++) {
            Student s("Name" + to_string(i), "Surname" + to_string(i), {}, 0);
            s.generateScores();  
            Class.push_back(s);
        }
    }
    else {
        ifstream file("Students.txt");
        if (!file)
        {
            cout << "Error: Could not open Students.txt" << endl;
            return 1;
        }
        string header;
        getline(file, header);
        Student student;
        while (file >> student)
        {
            Class.push_back(student);
        }
        file.close();
    }
    char formula;
    cout << "Would you like to use the average or the median to calculate the final grade?" << "\n";
    cout << "1: Average, 2: Median";
    cin >> formula;
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
    ofstream anwser("Anwser.txt");
    for (Student i : Class) cout << i << i.getFinalGrade(formula) << endl;
    for (Student i : Class) anwser << i << i.getFinalGrade(formula) << endl;
}
