
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using std::string;
using std::vector;
using std::cout;
using std::cin;

class Student {
    string name, surname;
    vector <int> Points;
    int exam;
    public:
    Student () {
        cout << "Input name: "; cin >> name;
        cout << "Input surname: "; cin >> surname;
        int n;
        while(true){
            cin >> n;
            Points.push_back(n);
            cout << "Want to input another point ? Y/N";
            string i; cin >> i;
            if (i == "n" || i == "N") break;
        }
            cout << "Input exam: ";
            cin >> exam;
        }
    Student (string n, string s, vector<int> P, int E) {
        name = n;
        surname = s;
        Points = P;
        exam = E;
    }
    void print() {
        cout << name << "|" << surname << "|";
        for (int i : Points) cout << i << "|";
        cout << exam << "\n";
    }
    
    ~Student () {
        name.clear();
        surname.clear();
        Points.clear();
        exam = 0;
    }
    void clear() {
        name.clear();
        surname.clear();
        Points.clear();
        exam = 0;
    }
    double results () {
        
};

int main () {
     vector <Student> Class;
     while(true){
            Student n;
            Class.push_back(n);
            n.clear();
            cout << "Want to input another Student ? Y/N";
            string i; cin >> i;
            if (i == "n" || i == "N") break;
        }
    for (Student i : Class) i.print();
}
