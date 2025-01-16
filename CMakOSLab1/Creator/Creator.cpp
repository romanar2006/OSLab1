#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>
#include "header.h"

int main(int argc, char* argv[]) {

    if (argc < 3) {
        std::cerr << "Wrong number of arguments. Try: Creator.exe <имя_файла> <количество_сотрудников>\n";
        return 1;
    }

    std::string binaryFileName = argv[1];
    int numRecords;

    try {
        numRecords = std::stoi(argv[2]);
        if (numRecords <= 0) throw std::invalid_argument("Number of employees must be positive");
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    std::ofstream outFile(binaryFileName, std::ios::binary);
    if (!outFile) {
        std::cerr << "Failed to open output file: " << binaryFileName << "\n";
        return 1;
    }

    std::vector<Employee> employees;
    for (int i = 0; i < numRecords; ++i) {
        Employee emp;

        while (true) {
            std::cout << "Enter employee number: ";
            if (!(std::cin >> emp.num) || emp.num <= 0) {
                std::cerr << "Error: number must be positive integer\n";
                clearInput();
            } else break;
        }

        std::cout << "Enter employee name: ";
        std::cin >> emp.name;

        while (true) {
            std::cout << "Enter number of hours: ";
            if (!(std::cin >> emp.hours) || emp.hours < 0) {
                std::cerr << "Error: can't be negative\n";
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
