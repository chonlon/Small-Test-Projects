/********************************************************************************
** Form generated from reading UI file 'ConditionSelectWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONDITIONSELECTWIDGET_H
#define UI_CONDITIONSELECTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QHBoxLayout *horizontalLayout;
    QGroupBox *group_box_1;
    QGridLayout *gridLayout;
    QDoubleSpinBox *spinbox_area_1_min;
    QComboBox *comboBox;
    QLabel *label_2;
    QDoubleSpinBox *spinbox_area_1_max;
    QLabel *label;
    QDoubleSpinBox *spinbox_contrast_1_min;
    QDoubleSpinBox *spinbox_contrast_1_max;
    QLabel *label_7;
    QLabel *label_8;
    QGroupBox *group_box_2;
    QGridLayout *gridLayout_4;
    QDoubleSpinBox *spinbox_area_2_min;
    QComboBox *combo_box_2;
    QLabel *label_9;
    QDoubleSpinBox *spinbox_area_2_max;
    QLabel *label_10;
    QDoubleSpinBox *spinbox_contrast_2_min;
    QDoubleSpinBox *spinbox_contrast_2_max;
    QLabel *label_11;
    QLabel *label_12;
    QGroupBox *group_box_3;
    QGridLayout *gridLayout_5;
    QDoubleSpinBox *spinbox_area_3_min;
    QComboBox *combo_box_3;
    QLabel *label_13;
    QDoubleSpinBox *spinbox_area_3_max;
    QLabel *label_14;
    QDoubleSpinBox *spinbox_contrast_3_min;
    QDoubleSpinBox *spinbox_contrast_3_max;
    QLabel *label_15;
    QLabel *label_16;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QStringLiteral("Form"));
        Form->resize(734, 139);
        Form->setStyleSheet(QStringLiteral("background-color: rgba(150, 150, 150, 20);"));
        horizontalLayout = new QHBoxLayout(Form);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        group_box_1 = new QGroupBox(Form);
        group_box_1->setObjectName(QStringLiteral("group_box_1"));
        group_box_1->setCheckable(true);
        gridLayout = new QGridLayout(group_box_1);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        spinbox_area_1_min = new QDoubleSpinBox(group_box_1);
        spinbox_area_1_min->setObjectName(QStringLiteral("spinbox_area_1_min"));

        gridLayout->addWidget(spinbox_area_1_min, 3, 1, 1, 1);

        comboBox = new QComboBox(group_box_1);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        gridLayout->addWidget(comboBox, 1, 0, 1, 3);

        label_2 = new QLabel(group_box_1);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 4, 0, 1, 1);

        spinbox_area_1_max = new QDoubleSpinBox(group_box_1);
        spinbox_area_1_max->setObjectName(QStringLiteral("spinbox_area_1_max"));

        gridLayout->addWidget(spinbox_area_1_max, 4, 1, 1, 1);

        label = new QLabel(group_box_1);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 3, 0, 1, 1);

        spinbox_contrast_1_min = new QDoubleSpinBox(group_box_1);
        spinbox_contrast_1_min->setObjectName(QStringLiteral("spinbox_contrast_1_min"));

        gridLayout->addWidget(spinbox_contrast_1_min, 3, 2, 1, 1);

        spinbox_contrast_1_max = new QDoubleSpinBox(group_box_1);
        spinbox_contrast_1_max->setObjectName(QStringLiteral("spinbox_contrast_1_max"));

        gridLayout->addWidget(spinbox_contrast_1_max, 4, 2, 1, 1);

        label_7 = new QLabel(group_box_1);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 2, 1, 1, 1);

        label_8 = new QLabel(group_box_1);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 2, 2, 1, 1);


        horizontalLayout->addWidget(group_box_1);

        group_box_2 = new QGroupBox(Form);
        group_box_2->setObjectName(QStringLiteral("group_box_2"));
        group_box_2->setCheckable(true);
        gridLayout_4 = new QGridLayout(group_box_2);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        spinbox_area_2_min = new QDoubleSpinBox(group_box_2);
        spinbox_area_2_min->setObjectName(QStringLiteral("spinbox_area_2_min"));

        gridLayout_4->addWidget(spinbox_area_2_min, 3, 1, 1, 1);

        combo_box_2 = new QComboBox(group_box_2);
        combo_box_2->setObjectName(QStringLiteral("combo_box_2"));

        gridLayout_4->addWidget(combo_box_2, 1, 0, 1, 3);

        label_9 = new QLabel(group_box_2);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_4->addWidget(label_9, 4, 0, 1, 1);

        spinbox_area_2_max = new QDoubleSpinBox(group_box_2);
        spinbox_area_2_max->setObjectName(QStringLiteral("spinbox_area_2_max"));

        gridLayout_4->addWidget(spinbox_area_2_max, 4, 1, 1, 1);

        label_10 = new QLabel(group_box_2);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_4->addWidget(label_10, 3, 0, 1, 1);

        spinbox_contrast_2_min = new QDoubleSpinBox(group_box_2);
        spinbox_contrast_2_min->setObjectName(QStringLiteral("spinbox_contrast_2_min"));

        gridLayout_4->addWidget(spinbox_contrast_2_min, 3, 2, 1, 1);

        spinbox_contrast_2_max = new QDoubleSpinBox(group_box_2);
        spinbox_contrast_2_max->setObjectName(QStringLiteral("spinbox_contrast_2_max"));

        gridLayout_4->addWidget(spinbox_contrast_2_max, 4, 2, 1, 1);

        label_11 = new QLabel(group_box_2);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout_4->addWidget(label_11, 2, 1, 1, 1);

        label_12 = new QLabel(group_box_2);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout_4->addWidget(label_12, 2, 2, 1, 1);


        horizontalLayout->addWidget(group_box_2);

        group_box_3 = new QGroupBox(Form);
        group_box_3->setObjectName(QStringLiteral("group_box_3"));
        group_box_3->setCheckable(true);
        gridLayout_5 = new QGridLayout(group_box_3);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        spinbox_area_3_min = new QDoubleSpinBox(group_box_3);
        spinbox_area_3_min->setObjectName(QStringLiteral("spinbox_area_3_min"));

        gridLayout_5->addWidget(spinbox_area_3_min, 3, 1, 1, 1);

        combo_box_3 = new QComboBox(group_box_3);
        combo_box_3->setObjectName(QStringLiteral("combo_box_3"));

        gridLayout_5->addWidget(combo_box_3, 1, 0, 1, 3);

        label_13 = new QLabel(group_box_3);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout_5->addWidget(label_13, 4, 0, 1, 1);

        spinbox_area_3_max = new QDoubleSpinBox(group_box_3);
        spinbox_area_3_max->setObjectName(QStringLiteral("spinbox_area_3_max"));

        gridLayout_5->addWidget(spinbox_area_3_max, 4, 1, 1, 1);

        label_14 = new QLabel(group_box_3);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout_5->addWidget(label_14, 3, 0, 1, 1);

        spinbox_contrast_3_min = new QDoubleSpinBox(group_box_3);
        spinbox_contrast_3_min->setObjectName(QStringLiteral("spinbox_contrast_3_min"));

        gridLayout_5->addWidget(spinbox_contrast_3_min, 3, 2, 1, 1);

        spinbox_contrast_3_max = new QDoubleSpinBox(group_box_3);
        spinbox_contrast_3_max->setObjectName(QStringLiteral("spinbox_contrast_3_max"));

        gridLayout_5->addWidget(spinbox_contrast_3_max, 4, 2, 1, 1);

        label_15 = new QLabel(group_box_3);
        label_15->setObjectName(QStringLiteral("label_15"));

        gridLayout_5->addWidget(label_15, 2, 1, 1, 1);

        label_16 = new QLabel(group_box_3);
        label_16->setObjectName(QStringLiteral("label_16"));

        gridLayout_5->addWidget(label_16, 2, 2, 1, 1);


        horizontalLayout->addWidget(group_box_3);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", Q_NULLPTR));
        group_box_1->setTitle(QApplication::translate("Form", "GroupBox", Q_NULLPTR));
        label_2->setText(QApplication::translate("Form", "\346\234\200\345\244\247\345\200\274:", Q_NULLPTR));
        label->setText(QApplication::translate("Form", "\346\234\200\345\260\217\345\200\274:", Q_NULLPTR));
        label_7->setText(QApplication::translate("Form", "\351\235\242\347\247\257", Q_NULLPTR));
        label_8->setText(QApplication::translate("Form", "\345\257\271\346\257\224\345\272\246", Q_NULLPTR));
        group_box_2->setTitle(QApplication::translate("Form", "GroupBox", Q_NULLPTR));
        label_9->setText(QApplication::translate("Form", "\346\234\200\345\244\247\345\200\274:", Q_NULLPTR));
        label_10->setText(QApplication::translate("Form", "\346\234\200\345\260\217\345\200\274:", Q_NULLPTR));
        label_11->setText(QApplication::translate("Form", "\351\235\242\347\247\257", Q_NULLPTR));
        label_12->setText(QApplication::translate("Form", "\345\257\271\346\257\224\345\272\246", Q_NULLPTR));
        group_box_3->setTitle(QApplication::translate("Form", "GroupBox", Q_NULLPTR));
        label_13->setText(QApplication::translate("Form", "\346\234\200\345\244\247\345\200\274:", Q_NULLPTR));
        label_14->setText(QApplication::translate("Form", "\346\234\200\345\260\217\345\200\274:", Q_NULLPTR));
        label_15->setText(QApplication::translate("Form", "\351\235\242\347\247\257", Q_NULLPTR));
        label_16->setText(QApplication::translate("Form", "\345\257\271\346\257\224\345\272\246", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONDITIONSELECTWIDGET_H
