#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm> 
#include <fstream> 
#include <Windows.h>

using namespace std;

enum Specialty {
    ComputerScience,
    Informatics,
    MathAndEconomics,
    PhysicsAndInformatics,
    LaborEducation
};

struct Student {
    string surname;
    int course;
    Specialty specialty;
    int physicsGrade;
    int mathGrade;
    int additionalGrade;
    double averageGrade;
};

bool compareStudents(const Student& a, const Student& b) {
    
    if (a.course != b.course)
        return a.course < b.course;
    
    if (a.averageGrade != b.averageGrade)
        return a.averageGrade > b.averageGrade;
    return a.surname > b.surname;
}

vector<Student> inputStudents(int n) {
    vector<Student> students(n);
    for (int i = 0; i < n; ++i) {
        cout << "Введіть дані для студента " << i + 1 << ":\n";
        cout << "Прізвище: ";
        cin >> students[i].surname;
        cout << "Курс: ";
        cin >> students[i].course;
        cout << "Спеціальність (0 - ComputerScience, 1 - Informatics, 2 - MathAndEconomics, 3 - PhysicsAndInformatics, 4 - LaborEducation): ";
        int specialty;
        cin >> specialty;
        students[i].specialty = static_cast<Specialty>(specialty);
        cout << "Оцінка з фізики: ";
        cin >> students[i].physicsGrade;
        cout << "Оцінка з математики: ";
        cin >> students[i].mathGrade;
        switch (students[i].specialty) {
        case ComputerScience:
            cout << "Оцінка з програмування: ";
            break;
        case Informatics:
            cout << "Оцінка з чисельних методів: ";
            break;
        default:
            cout << "Оцінка з педагогіки: ";
            break;
        }
        cin >> students[i].additionalGrade;
        students[i].averageGrade = (students[i].physicsGrade + students[i].mathGrade + students[i].additionalGrade) / 3.0;
    }
    
    sort(students.begin(), students.end(), compareStudents);
    return students;
}

void printStudents(const vector<Student>& students) {
    cout << "========================================================================================================" << endl;
    cout << "| # | Surname       | Course | Specialization               | Physics | Mathematics | Additional Grade | Average Grade |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < students.size(); ++i) {
        cout << "| " << setw(1) << right << i + 1 << " | ";
        cout << setw(13) << left << students[i].surname << " | ";
        cout << setw(6) << right << students[i].course << " | ";
        switch (students[i].specialty) {
        case ComputerScience:
            cout << setw(28) << left << "Computer Science" << " | ";
            break;
        case Informatics:
            cout << setw(28) << left << "Informatics" << " | ";
            break;
        case MathAndEconomics:
            cout << setw(28) << left << "Math and Economics" << " | ";
            break;
        case PhysicsAndInformatics:
            cout << setw(28) << left << "Physics and Informatics" << " | ";
            break;
        case LaborEducation:
            cout << setw(28) << left << "LaborEducation" << " | ";
            break;
        }
        cout << setw(7) << right << students[i].physicsGrade << " | ";
        cout << setw(11) << right << students[i].mathGrade << " | ";
        cout << setw(16) << right << students[i].additionalGrade << " | ";
        cout << setw(13) << right << fixed << setprecision(2) << students[i].averageGrade << " |\n";
    }
    cout << "========================================================================================================" << endl;
}

void printStudent(const Student& student) {
    cout << "========================================================================================================" << endl;
    cout << "| Surname       | Course | Specialization               | Physics | Mathematics | Additional Grade | Average Grade |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    cout << "| ";
    cout << setw(13) << left << student.surname << " | ";
    cout << setw(6) << right << student.course << " | ";
    switch (student.specialty) {
    case ComputerScience:
        cout << setw(28) << left << "Computer Science" << " | ";
        break;
    case Informatics:
        cout << setw(28) << left << "Informatics" << " | ";
        break;
    case MathAndEconomics:
        cout << setw(28) << left << "Math and Economics" << " | ";
        break;
    case PhysicsAndInformatics:
        cout << setw(28) << left << "Physics and Informatics" << " | ";
        break;
    case LaborEducation:
        cout << setw(28) << left << "LaborEducation" << " | ";
        break;
    }
    cout << setw(7) << right << student.physicsGrade << " | ";
    cout << setw(11) << right << student.mathGrade << " | ";
    cout << setw(16) << right << student.additionalGrade << " | ";
    cout << setw(13) << right << fixed << setprecision(2) << student.averageGrade << " |\n";
    cout << "========================================================================================================" << endl;
}

void searchStudent(const vector<Student>& students) {
    string surname;
    cout << "Введіть прізвище студента: ";
    cin >> surname;
    for (const auto& student : students) {
        if (student.surname == surname) {
            printStudent(student);
            return;
        }
    }
    cout << "Студент з таким прізвищем не знайдений.\n";
}

void saveStudentsToBinaryFile(const vector<Student>& students, const string& filename) {
    ofstream file(filename, ios::out | ios::binary);
    if (!file.is_open()) {
        cout << "Помилка відкриття файлу для запису.\n";
        return;
    }
    for (const auto& student : students) {
        file.write(reinterpret_cast<const char*>(&student), sizeof(Student));
    }
    file.close();
    cout << "Дані студентів збережено у бінарний файл " << filename << ".\n";
}

int main() {
    SetConsoleOutputCP(1251);
    int n;
    cout << "Введіть кількість студентів: ";
    cin >> n;

    vector<Student> students = inputStudents(n);

    printStudents(students);

    searchStudent(students);

    
    saveStudentsToBinaryFile(students, "students.bin");

    return 0;
}
