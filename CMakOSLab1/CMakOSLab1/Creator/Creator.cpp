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
        std::cerr << "������������ ����������. �����������: Creator.exe <���_�����> <����������_�����������>\n";
        return 1;
    }

    std::string binaryFileName = argv[1];
    int numRecords;

    try {
        numRecords = std::stoi(argv[2]);
        if (numRecords <= 0) throw std::invalid_argument("���������� ����������� ������ ���� �������������");
    } catch (const std::exception& e) {
        std::cerr << "������: " << e.what() << "\n";
        return 1;
    }

    std::ofstream outFile(binaryFileName, std::ios::binary);
    if (!outFile) {
        std::cerr << "�� ������� ������� ���� ��� ������: " << binaryFileName << "\n";
        return 1;
    }

    std::vector<Employee> employees;
    for (int i = 0; i < numRecords; ++i) {
        Employee emp;

        while (true) {
            std::cout << "������� ����� ����������: ";
            if (!(std::cin >> emp.num) || emp.num <= 0) {
                std::cerr << "������: ����� ������ ���� ����������� ������\n";
                clearInput();
            } else break;
        }

        std::cout << "������� ��� ����������: ";
        std::cin >> emp.name;

        while (true) {
            std::cout << "������� ����� ������������ �����: ";
            if (!(std::cin >> emp.hours) || emp.hours < 0) {
                std::cerr << "������: ���� ������ ���� ��������������� ������\n";
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
