#include <QtTest/QtTest>
#include "header.h"
#include <QObject>

// Test class inheriting from QObject
class Test1 : public QObject
{
    Q_OBJECT

private slots:
    void testEmployeeNum();
    void testEmployeeHours();
    void testClearInput();
};

void Test1::testEmployeeNum() {
    Employee emp;
    emp.num = 5;
    QVERIFY(emp.num > 0);
}

void Test1::testEmployeeHours() {
    Employee emp;
    emp.hours = 40.0;
    QVERIFY(emp.hours >= 0);
}

void Test1::testClearInput() {
    std::istringstream fakeInput("abc\n123\n");
    std::cin.rdbuf(fakeInput.rdbuf());

    int number;
    std::cin >> number;
    QVERIFY(!std::cin.good());
    clearInput();
    std::cin >> number;
    QVERIFY(std::cin.good());
    QVERIFY(number == 123);
}

QTEST_MAIN(Test1)
#include "tst_test1.moc"
