#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <windows.h>
#include <limits>
#include <vector>
#include "header.h"

int main() {

    std::string binaryFileName, reportFileName;
    int numRecords;
    double hourlyRate;

    std::cout << "Enter binary file name: ";
    std::cin >> binaryFileName;

    while (true) {
        std::cout << "Enter number of employees: ";
        if (!(std::cin >> numRecords) || numRecords <= 0) {
            std::cerr << "Something wrong, positive integer\n";
            clearInput();
        } else break;
    }

    std::string creatorCmd = "Creator.exe " + binaryFileName + " " + std::to_string(numRecords);

    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    std::vector<char> creatorCmdVec(creatorCmd.begin(), creatorCmd.end());
    creatorCmdVec.push_back('\0');

    if (!CreateProcessA(NULL, creatorCmdVec.data(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        std::cerr << "Creator wasn't created, last error code: " << GetLastError() << "\n";
        return 1;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    std::cout << "Enter report file name: ";
    std::cin >> reportFileName;

    while (true) {
        std::cout << "Enter hourly rate: ";
        if (!(std::cin >> hourlyRate) || hourlyRate <= 0) {
            std::cerr << "Something wrong, positive\n";
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
        std::cerr << "Failed to open report file: " << reportFileName << "\n";
        return 1;
    }

    std::string line;
    std::cout << "\nReport file:\n";
    while (std::getline(reportFile, line)) {
        std::cout << line << "\n";
    }
    reportFile.close();

    return 0;
}
