#pragma once
#include <QtWidgets>
#include <QtTest/QtTest>

class TestGui : public QObject
{
    Q_OBJECT

private slots:
    void testGui_data();
    void testGui();
};