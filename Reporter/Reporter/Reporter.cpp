#include <iostream>
#include <fstream>
#include <iomanip>
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

    ifstream inFile(argv[1], ios::binary);
    if (!inFile) {
        cerr << "Не открывается бинарный файл\n";
        return 1;
    }

    ofstream outFile(argv[2]);
    if (!outFile) {
        cerr << "Не открывается файл отчета\n";
        return 1;
    }

    double hourlyRate;
    try {
        hourlyRate = stod(argv[3]);
        if (hourlyRate <= 0) throw invalid_argument("Неверная ставка");
    }
    catch (const exception& e) {
        cerr << "Что-то не то: " << e.what() << "\n";
        return 1;
    }

    vector<Employee> employees;
    Employee emp;

    while (inFile.read(reinterpret_cast<char*>(&emp), sizeof(Employee))) {
        employees.push_back(emp);
    }

    sort(employees.begin(), employees.end(), [](const Employee& a, const Employee& b) {
        return a.num < b.num;
        });

    outFile << "Отчет по файлу \"" << argv[1] << "\"\n";
    outFile << left << setw(15) << "Номер"
        << setw(20) << "Имя"
        << setw(10) << "Часы"
        << setw(15) << "Зарплата\n";

    cout << left << setw(15) << "Номер"
        << setw(20) << "Имя"
        << setw(10) << "Часы"
        << setw(15) << "Зарплата\n";

    for (const auto& e : employees) {
        double salary = e.hours * hourlyRate;
        outFile << left << setw(15) << e.num
            << setw(20) << e.name
            << setw(10) << e.hours
            << setw(15) << salary << "\n";

        cout << left << setw(15) << e.num
            << setw(20) << e.name
            << setw(10) << e.hours
            << setw(15) << salary << "\n";
    }

    inFile.close();
    outFile.close();
    return 0;
}
