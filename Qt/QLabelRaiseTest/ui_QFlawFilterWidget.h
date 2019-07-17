/********************************************************************************
** Form generated from reading UI file 'QFlawFilterWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QFLAWFILTERWIDGET_H
#define UI_QFLAWFILTERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UI
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QGroupBox *contrast_ratio_groupbox;
    QGridLayout *gridLayout;
    QLabel *label;
    QDoubleSpinBox *contrast_ratio_groupbox_spinbox_min;
    QLabel *label_3;
    QDoubleSpinBox *contrast_ratio_groupbox_spinbox_max;
    QGroupBox *area_groupbox;
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QDoubleSpinBox *area_double_spinbox_min;
    QLabel *label_4;
    QDoubleSpinBox *area_double_spinbox_max;
    QPushButton *filter_button;
    QTableView *tableView;

    void setupUi(QWidget *UI)
    {
        if (UI->objectName().isEmpty())
            UI->setObjectName(QStringLiteral("UI"));
        UI->resize(675, 511);
        verticalLayout = new QVBoxLayout(UI);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        contrast_ratio_groupbox = new QGroupBox(UI);
        contrast_ratio_groupbox->setObjectName(QStringLiteral("contrast_ratio_groupbox"));
        contrast_ratio_groupbox->setCheckable(true);
        gridLayout = new QGridLayout(contrast_ratio_groupbox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(contrast_ratio_groupbox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        contrast_ratio_groupbox_spinbox_min = new QDoubleSpinBox(contrast_ratio_groupbox);
        contrast_ratio_groupbox_spinbox_min->setObjectName(QStringLiteral("contrast_ratio_groupbox_spinbox_min"));

        gridLayout->addWidget(contrast_ratio_groupbox_spinbox_min, 0, 1, 1, 1);

        label_3 = new QLabel(contrast_ratio_groupbox);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        contrast_ratio_groupbox_spinbox_max = new QDoubleSpinBox(contrast_ratio_groupbox);
        contrast_ratio_groupbox_spinbox_max->setObjectName(QStringLiteral("contrast_ratio_groupbox_spinbox_max"));

        gridLayout->addWidget(contrast_ratio_groupbox_spinbox_max, 1, 1, 1, 1);


        horizontalLayout->addWidget(contrast_ratio_groupbox);

        area_groupbox = new QGroupBox(UI);
        area_groupbox->setObjectName(QStringLiteral("area_groupbox"));
        area_groupbox->setCheckable(true);
        area_groupbox->setChecked(false);
        gridLayout_2 = new QGridLayout(area_groupbox);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_2 = new QLabel(area_groupbox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        area_double_spinbox_min = new QDoubleSpinBox(area_groupbox);
        area_double_spinbox_min->setObjectName(QStringLiteral("area_double_spinbox_min"));

        gridLayout_2->addWidget(area_double_spinbox_min, 0, 1, 1, 1);

        label_4 = new QLabel(area_groupbox);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 1, 0, 1, 1);

        area_double_spinbox_max = new QDoubleSpinBox(area_groupbox);
        area_double_spinbox_max->setObjectName(QStringLiteral("area_double_spinbox_max"));

        gridLayout_2->addWidget(area_double_spinbox_max, 1, 1, 1, 1);


        horizontalLayout->addWidget(area_groupbox);

        filter_button = new QPushButton(UI);
        filter_button->setObjectName(QStringLiteral("filter_button"));

        horizontalLayout->addWidget(filter_button);


        verticalLayout->addLayout(horizontalLayout);

        tableView = new QTableView(UI);
        tableView->setObjectName(QStringLiteral("tableView"));

        verticalLayout->addWidget(tableView);


        retranslateUi(UI);

        QMetaObject::connectSlotsByName(UI);
    } // setupUi

    void retranslateUi(QWidget *UI)
    {
        UI->setWindowTitle(QApplication::translate("UI", "Form", Q_NULLPTR));
        contrast_ratio_groupbox->setTitle(QApplication::translate("UI", "\345\257\271\346\257\224\345\272\246", Q_NULLPTR));
        label->setText(QApplication::translate("UI", "\346\234\200\345\260\217\345\200\274:", Q_NULLPTR));
        label_3->setText(QApplication::translate("UI", "\346\234\200\345\244\247\345\200\274:", Q_NULLPTR));
        area_groupbox->setTitle(QApplication::translate("UI", "\351\235\242\347\247\257", Q_NULLPTR));
        label_2->setText(QApplication::translate("UI", "\346\234\200\345\260\217\345\200\274:", Q_NULLPTR));
        label_4->setText(QApplication::translate("UI", "\346\234\200\345\244\247\345\200\274:", Q_NULLPTR));
        filter_button->setText(QApplication::translate("UI", "\347\255\233\351\200\211", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class UI: public Ui_UI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QFLAWFILTERWIDGET_H
