#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <windows.h>
#include <limits>
#include <vector>
#include "header.h"

int main() {
    setlocale(LC_ALL, "Russian");

    std::string binaryFileName, reportFileName;
    int numRecords;
    double hourlyRate;

    std::cout << "Введите имя бинарного файла: ";
    std::cin >> binaryFileName;

    while (true) {
        std::cout << "Введите количество сотрудников: ";
        if (!(std::cin >> numRecords) || numRecords <= 0) {
            std::cerr << "Что-то не то, натуральное число\n";
            clearInput();
        } else break;
    }

    std::string creatorCmd = "Creator.exe " + binaryFileName + " " + std::to_string(numRecords);

    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    std::vector<char> creatorCmdVec(creatorCmd.begin(), creatorCmd.end());
    creatorCmdVec.push_back('\0');

    if (!CreateProcessA(NULL, creatorCmdVec.data(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        std::cerr << "Creator не запускается, код последней ошибки: " << GetLastError() << "\n";
        return 1;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    std::cout << "Введите имя отчётного файла: ";
    std::cin >> reportFileName;

    while (true) {
        std::cout << "Введите почасовую оплату: ";
        if (!(std::cin >> hourlyRate) || hourlyRate <= 0) {
            std::cerr << "Что-то не то, нужно положительное число\n";
            clearInput();
        } else break;
    }

    std::string reporterCmd = "Reporter.exe " + binaryFileName + " " + reportFileName + " " + std::to_string(hourlyRate);

    if (!CreateProcessA(NULL, &reporterCmd[0], NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        std::cerr << "Reporter не запускается, код последней ошибки: " << GetLastError() << "\n";
        return 1;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    std::ifstream reportFile(reportFileName);
    if (!reportFile) {
        std::cerr << "Не удается открыть отчётный файл: " << reportFileName << "\n";
        return 1;
    }

    std::string line;
    std::cout << "\nСодержимое отчётного файла:\n";
    while (std::getline(reportFile, line)) {
        std::cout << line << "\n";
    }
    reportFile.close();

    return 0;
}
