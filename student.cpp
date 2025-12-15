#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

class Student {
public:
    string usn;
    string name;
    int marks1, marks2, marks3;
    int total;
    float average;

    void calculate() {
        total = marks1 + marks2 + marks3;
        average = total / 3.0;
    }
};

vector<Student> students;

void loadData() {
    students.clear();
    ifstream file("students.txt");
    Student s;
    while (file >> s.usn >> s.name >> s.marks1 >> s.marks2 >> s.marks3) {
        s.calculate();
        students.push_back(s);
    }
    file.close();
}

void saveStudent(Student s) {
    ofstream file("students.txt", ios::app);
    file << s.usn << " " << s.name << " " << s.marks1 << " " << s.marks2 << " " << s.marks3 << endl;
    file.close();
}

void addStudent() {
    Student s;
    cout << "\n--- Add Student Details ---\n";
    cout << "Enter USN: "; cin >> s.usn;
    cout << "Enter Name: "; cin >> s.name;
    cout << "Enter Marks 1: "; cin >> s.marks1;
    cout << "Enter Marks 2: "; cin >> s.marks2;
    cout << "Enter Marks 3: "; cin >> s.marks3;

    s.calculate();
    saveStudent(s);
    cout << "Student record added successfully!\n";
}

void viewResults() {
    loadData();
    cout << "\n---------------- STUDENT RESULTS ----------------\n";
    cout << left << setw(12) << "USN" << setw(15) << "Name" << setw(8)
         << "M1" << setw(8) << "M2" << setw(8) << "M3"
         << setw(8) << "Total" << setw(8) << "Avg" << endl;

    for (auto s : students) {
        cout << left << setw(12) << s.usn << setw(15) << s.name
             << setw(8) << s.marks1 << setw(8) << s.marks2
             << setw(8) << s.marks3 << setw(8) << s.total
             << setw(8) << fixed << setprecision(2) << s.average << endl;
    }
}

void searchByUSN() {
    loadData();
    string key;
    cout << "\nEnter USN to search: ";
    cin >> key;

    for (auto s : students) {
        if (s.usn == key) {
            cout << "\nStudent Found!\n";
            cout << "Name: " << s.name << endl;
            cout << "Marks: " << s.marks1 << ", " << s.marks2 << ", " << s.marks3 << endl;
            cout << "Total: " << s.total << endl;
            cout << "Average: " << s.average << endl;
            return;
        }
    }
    cout << "Student not found!\n";
}

bool adminLogin() {
    string user, pass;
    cout << "\n--- Admin Login ---\n";
    cout << "Username: "; cin >> user;
    cout << "Password: "; cin >> pass;

    return (user == "admin" && pass == "1234");
}

void adminPanel() {
    int choice;
    do {
        cout << "\n========== ADMIN PANEL ==========";
        cout << "\n1. Add Student Details";
        cout << "\n2. View All Results";
        cout << "\n3. Search Student by USN";
        cout << "\n4. Logout";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewResults(); break;
            case 3: searchByUSN(); break;
            case 4: cout << "Logging out..."; break;
            default: cout << "Invalid choice!";
        }
    } while (choice != 4);
}

int main() {
    int choice;
    do {
        cout << "\n====================================";
        cout << "\n STUDENT RESULT MANAGEMENT SYSTEM";
        cout << "\n====================================";
        cout << "\n1. Admin Login";
        cout << "\n2. View Results";
        cout << "\n3. Search Result";
        cout << "\n4. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (adminLogin()) adminPanel();
                else cout << "Invalid login!";
                break;
            case 2: viewResults(); break;
            case 3: searchByUSN(); break;
            case 4: cout << "Thank you!"; break;
            default: cout << "Invalid option!";
        }
    } while (choice != 4);

    return 0;
}