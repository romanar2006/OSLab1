#ifndef HEADER_H
#define HEADER_H

#include <limits>
#include <iostream>
#include <string>

using namespace std;

struct Employee {
    int num;
    char name[10];
    double hours;
};

// Общая функция для очистки ввода
inline void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

#endif // HEADER_H
