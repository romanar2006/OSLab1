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
        std::cerr << "�� ����������� �������� ����\n";
        return 1;
    }

    std::ofstream outFile(argv[2]);
    if (!outFile) {
        std::cerr << "�� ����������� ���� ������\n";
        return 1;
    }

    double hourlyRate;
    try {
        hourlyRate = std::stod(argv[3]);
        if (hourlyRate <= 0) throw std::invalid_argument("�������� ������");
    } catch (const std::exception& e) {
        std::cerr << "���-�� �� ��: " << e.what() << "\n";
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

    outFile << "����� �� ����� \"" << argv[1] << "\"\n";
    outFile << std::left << std::setw(15) << "�����"
            << std::setw(20) << "���"
            << std::setw(10) << "����"
            << std::setw(15) << "��������\n";

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
