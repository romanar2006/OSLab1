#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Employee {
    int num;
    char name[10];
    double hours;
};

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    ofstream outFile(argv[1], ios::binary);
    if (!outFile) {
        cerr << "Файл не открывается\n";
        return 1;
    }

    int numRecords;
    try {
        numRecords = stoi(argv[2]);
        if (numRecords <= 0) throw invalid_argument("Неверное число");
    }
    catch (const exception& e) {
        cerr << "Что-то не то: " << e.what() << "\n";
        return 1;
    }

    vector<Employee> employees;
    for (int i = 0; i < numRecords; ++i) {
        Employee emp;

        while (true) {
            cout << "Введите номер сотрудника: ";
            if (!(cin >> emp.num) || emp.num <= 0) {
                cerr << "Что-то не то, нужно натуральное число\n";
                clearInput();
            }
            else break;
        }

        cout << "Введите имя сотрудника: ";
        cin >> emp.name;

        while (true) {
            cout << "Введите число отработанных часов: ";
            if (!(cin >> emp.hours) || emp.hours < 0) {
                cerr << "Что-то не то, нужно неотрицательное число\n";
                clearInput();
            }
            else break;
        }

        employees.push_back(emp);
    }

    sort(employees.begin(), employees.end(), [](const Employee& a, const Employee& b) {
        return a.num < b.num;
        });

    for (const auto& emp : employees) {
        outFile.write(reinterpret_cast<const char*>(&emp), sizeof(Employee));
    }

    outFile.close();
    return 0;
}
