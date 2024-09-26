#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>
#include "header.h"

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    if (argc < 3) {
        std::cerr << "Недостаточно аргументов. Используйте: Creator.exe <имя_файла> <количество_сотрудников>\n";
        return 1;
    }

    std::string binaryFileName = argv[1];
    int numRecords;

    try {
        numRecords = std::stoi(argv[2]);
        if (numRecords <= 0) throw std::invalid_argument("Количество сотрудников должно быть положительным");
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
        return 1;
    }

    std::ofstream outFile(binaryFileName, std::ios::binary);
    if (!outFile) {
        std::cerr << "Не удается открыть файл для записи: " << binaryFileName << "\n";
        return 1;
    }

    std::vector<Employee> employees;
    for (int i = 0; i < numRecords; ++i) {
        Employee emp;

        while (true) {
            std::cout << "Введите номер сотрудника: ";
            if (!(std::cin >> emp.num) || emp.num <= 0) {
                std::cerr << "Ошибка: Номер должен быть натуральным числом\n";
                clearInput();
            } else break;
        }

        std::cout << "Введите имя сотрудника: ";
        std::cin >> emp.name;

        while (true) {
            std::cout << "Введите число отработанных часов: ";
            if (!(std::cin >> emp.hours) || emp.hours < 0) {
                std::cerr << "Ошибка: Часы должны быть неотрицательным числом\n";
                clearInput();
            } else break;
        }

        employees.push_back(emp);
    }

    std::sort(employees.begin(), employees.end(), [](const Employee& a, const Employee& b) {
        return a.num < b.num;
    });

    for (const auto& emp : employees) {
        outFile.write(reinterpret_cast<const char*>(&emp), sizeof(Employee));
    }

    outFile.close();
    return 0;
}
