#include"testrunner.h"
#include "TestGui.h"
#include <QDebug>
#include <QApplication>


int main(int argc, char* argv[])
{
    TestRunner testRunner;

    //your QTest compatible class here
    testRunner.addTest(new TestGui);
    //testRunner.addTest(new Test2);

    bool pass = testRunner.runTests(argc, argv);
    qDebug() << "Overall result:" << (pass ? "PASS" : "FAIL");
    return pass ? 0 : 1;
}