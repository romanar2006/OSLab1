#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#define NOMINMAX
#include <windows.h>

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

int main() {
    setlocale(LC_ALL, "Russian");

    string binaryFileName, reportFileName;
    int numRecords;
    double hourlyRate;

    cout << "Введите имя бинарного файла: ";
    cin >> binaryFileName;

    while (true) {
        cout << "Введите количество сотрудников: ";
        if (!(cin >> numRecords) || numRecords <= 0) {
            cerr << "Что-то не то, натуральное число\n";
            clearInput();
        }
        else break;
    }

    string creatorCmd = "Creator.exe " + binaryFileName + " " + to_string(numRecords);

    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;

    if (!CreateProcessA(NULL, &creatorCmd[0], NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        cerr << "Creator не запускается, код последней ошибки: " << GetLastError() << "\n";
        return 1;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    cout << "Введите имя отчётного файла: ";
    cin >> reportFileName;

    while (true) {
        cout << "Введите почасовую оплату: ";
        if (!(cin >> hourlyRate) || hourlyRate <= 0) {
            cerr << "Что-то не то, нужно положительное число\n";
            clearInput();
        }
        else break;
    }

    string reporterCmd = "Reporter.exe " + binaryFileName + " " + reportFileName + " " + to_string(hourlyRate);

    if (!CreateProcessA(NULL, &reporterCmd[0], NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        cerr << "Reporter не запускается, код последней ошибки: " << GetLastError() << "\n";
        return 1;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    ifstream reportFile(reportFileName);
    string line;
    cout << "\nСодержимое отчётного файла:\n";
    while (getline(reportFile, line)) {
        cout << line << "\n";
    }
    reportFile.close();

    return 0;
}
