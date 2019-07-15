/********************************************************************************
** Form generated from reading UI file 'FlawSelectWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FLAWSELECTWIDGET_H
#define UI_FLAWSELECTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FlawSelectWidgetBottom
{
public:
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QDoubleSpinBox *doubleSpinBox_3;
    QDoubleSpinBox *doubleSpinBox_4;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QDoubleSpinBox *doubleSpinBox_5;
    QDoubleSpinBox *doubleSpinBox_6;
    QPushButton *pushButton;
    QTableView *tableView;

    void setupUi(QWidget *FlawSelectWidgetBottom)
    {
        if (FlawSelectWidgetBottom->objectName().isEmpty())
            FlawSelectWidgetBottom->setObjectName(QStringLiteral("FlawSelectWidgetBottom"));
        FlawSelectWidgetBottom->resize(675, 511);
        verticalLayout_6 = new QVBoxLayout(FlawSelectWidgetBottom);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        groupBox = new QGroupBox(FlawSelectWidgetBottom);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setCheckable(true);
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        doubleSpinBox_3 = new QDoubleSpinBox(groupBox);
        doubleSpinBox_3->setObjectName(QStringLiteral("doubleSpinBox_3"));

        verticalLayout->addWidget(doubleSpinBox_3);

        doubleSpinBox_4 = new QDoubleSpinBox(groupBox);
        doubleSpinBox_4->setObjectName(QStringLiteral("doubleSpinBox_4"));

        verticalLayout->addWidget(doubleSpinBox_4);


        verticalLayout_3->addLayout(verticalLayout);


        horizontalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(FlawSelectWidgetBottom);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setCheckable(true);
        groupBox_2->setChecked(false);
        verticalLayout_4 = new QVBoxLayout(groupBox_2);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        doubleSpinBox_5 = new QDoubleSpinBox(groupBox_2);
        doubleSpinBox_5->setObjectName(QStringLiteral("doubleSpinBox_5"));

        verticalLayout_2->addWidget(doubleSpinBox_5);

        doubleSpinBox_6 = new QDoubleSpinBox(groupBox_2);
        doubleSpinBox_6->setObjectName(QStringLiteral("doubleSpinBox_6"));

        verticalLayout_2->addWidget(doubleSpinBox_6);


        verticalLayout_4->addLayout(verticalLayout_2);


        horizontalLayout->addWidget(groupBox_2);

        pushButton = new QPushButton(FlawSelectWidgetBottom);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);


        verticalLayout_5->addLayout(horizontalLayout);

        tableView = new QTableView(FlawSelectWidgetBottom);
        tableView->setObjectName(QStringLiteral("tableView"));

        verticalLayout_5->addWidget(tableView);


        verticalLayout_6->addLayout(verticalLayout_5);


        retranslateUi(FlawSelectWidgetBottom);

        QMetaObject::connectSlotsByName(FlawSelectWidgetBottom);
    } // setupUi

    void retranslateUi(QWidget *FlawSelectWidgetBottom)
    {
        FlawSelectWidgetBottom->setWindowTitle(QApplication::translate("FlawSelectWidgetBottom", "Form", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("FlawSelectWidgetBottom", "\345\257\271\346\257\224\345\272\246", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("FlawSelectWidgetBottom", "\351\235\242\347\247\257", Q_NULLPTR));
        pushButton->setText(QApplication::translate("FlawSelectWidgetBottom", "\347\255\233\351\200\211", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class FlawSelectWidgetBottom: public Ui_FlawSelectWidgetBottom {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FLAWSELECTWIDGET_H
