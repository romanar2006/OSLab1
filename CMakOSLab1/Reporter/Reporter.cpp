#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include "header.h"

int main(int argc, char* argv[]) {

    std::ifstream inFile(argv[1], std::ios::binary);
    if (!inFile) {
        std::cerr << "Failed to open binary file\n";
        return 1;
    }

    std::ofstream outFile(argv[2]);
    if (!outFile) {
        std::cerr << "Failed to open report file\n";
        return 1;
    }

    double hourlyRate;
    try {
        hourlyRate = std::stod(argv[3]);
        if (hourlyRate <= 0) throw std::invalid_argument("Wrong number");
    } catch (const std::exception& e) {
        std::cerr << "Something wrong: " << e.what() << "\n";
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

    outFile << "Report of file \"" << argv[1] << "\"\n";
    outFile << std::left << std::setw(15) << "Number"
            << std::setw(20) << "Name"
            << std::setw(10) << "Hours"
            << std::setw(15) << "Salary\n";

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
