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
    QGroupBox *contrast_ratio_groupbox;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QDoubleSpinBox *contrast_ratio_groupbox_spinbox_min;
    QDoubleSpinBox *contrast_ratio_groupbox_spinbox_max;
    QGroupBox *area_groupbox;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QDoubleSpinBox *area_double_spinbox_min;
    QDoubleSpinBox *area_double_spinbox_max;
    QPushButton *filter_button;
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
        contrast_ratio_groupbox = new QGroupBox(FlawSelectWidgetBottom);
        contrast_ratio_groupbox->setObjectName(QStringLiteral("contrast_ratio_groupbox"));
        contrast_ratio_groupbox->setCheckable(true);
        verticalLayout_3 = new QVBoxLayout(contrast_ratio_groupbox);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        contrast_ratio_groupbox_spinbox_min = new QDoubleSpinBox(contrast_ratio_groupbox);
        contrast_ratio_groupbox_spinbox_min->setObjectName(QStringLiteral("contrast_ratio_groupbox_spinbox_min"));

        verticalLayout->addWidget(contrast_ratio_groupbox_spinbox_min);

        contrast_ratio_groupbox_spinbox_max = new QDoubleSpinBox(contrast_ratio_groupbox);
        contrast_ratio_groupbox_spinbox_max->setObjectName(QStringLiteral("contrast_ratio_groupbox_spinbox_max"));

        verticalLayout->addWidget(contrast_ratio_groupbox_spinbox_max);


        verticalLayout_3->addLayout(verticalLayout);


        horizontalLayout->addWidget(contrast_ratio_groupbox);

        area_groupbox = new QGroupBox(FlawSelectWidgetBottom);
        area_groupbox->setObjectName(QStringLiteral("area_groupbox"));
        area_groupbox->setCheckable(true);
        area_groupbox->setChecked(false);
        verticalLayout_4 = new QVBoxLayout(area_groupbox);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        area_double_spinbox_min = new QDoubleSpinBox(area_groupbox);
        area_double_spinbox_min->setObjectName(QStringLiteral("area_double_spinbox_min"));

        verticalLayout_2->addWidget(area_double_spinbox_min);

        area_double_spinbox_max = new QDoubleSpinBox(area_groupbox);
        area_double_spinbox_max->setObjectName(QStringLiteral("area_double_spinbox_max"));

        verticalLayout_2->addWidget(area_double_spinbox_max);


        verticalLayout_4->addLayout(verticalLayout_2);


        horizontalLayout->addWidget(area_groupbox);

        filter_button = new QPushButton(FlawSelectWidgetBottom);
        filter_button->setObjectName(QStringLiteral("filter_button"));

        horizontalLayout->addWidget(filter_button);


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
        contrast_ratio_groupbox->setTitle(QApplication::translate("FlawSelectWidgetBottom", "\345\257\271\346\257\224\345\272\246", Q_NULLPTR));
        area_groupbox->setTitle(QApplication::translate("FlawSelectWidgetBottom", "\351\235\242\347\247\257", Q_NULLPTR));
        filter_button->setText(QApplication::translate("FlawSelectWidgetBottom", "\347\255\233\351\200\211", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class FlawSelectWidgetBottom: public Ui_FlawSelectWidgetBottom {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FLAWSELECTWIDGET_H
