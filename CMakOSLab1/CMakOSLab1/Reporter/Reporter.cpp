#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include "header.h"

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    std::ifstream inFile(argv[1], std::ios::binary);
    if (!inFile) {
        std::cerr << "Не открывается бинарный файл\n";
        return 1;
    }

    std::ofstream outFile(argv[2]);
    if (!outFile) {
        std::cerr << "Не открывается файл отчета\n";
        return 1;
    }

    double hourlyRate;
    try {
        hourlyRate = std::stod(argv[3]);
        if (hourlyRate <= 0) throw std::invalid_argument("Неверная ставка");
    } catch (const std::exception& e) {
        std::cerr << "Что-то не то: " << e.what() << "\n";
        return 1;
    }

    std::vector<Employee> employees;
    Employee emp;

    while (inFile.read(reinterpret_cast<char*>(&emp), sizeof(Employee))) {
        employees.push_back(emp);
    }

    std::sort(employees.begin(), employees.end(), [](const Employee& a, const Employee& b) {
        return a.num < b.num;
    });

    outFile << "Отчет по файлу \"" << argv[1] << "\"\n";
    outFile << std::left << std::setw(15) << "Номер"
            << std::setw(20) << "Имя"
            << std::setw(10) << "Часы"
            << std::setw(15) << "Зарплата\n";

    for (const auto& e : employees) {
        double salary = e.hours * hourlyRate;
        outFile << std::left << std::setw(15) << e.num
                << std::setw(20) << e.name
                << std::setw(10) << e.hours
                << std::setw(15) << salary << "\n";
    }

    inFile.close();
    outFile.close();
    return 0;
}
