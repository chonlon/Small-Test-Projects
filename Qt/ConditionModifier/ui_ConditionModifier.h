/********************************************************************************
** Form generated from reading UI file 'ConditionModifier.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONDITIONMODIFIER_H
#define UI_CONDITIONMODIFIER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConditionModifierClass
{
public:
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QWidget *button_group_container;
    QVBoxLayout *verticalLayout;
    QPushButton *add_button;
    QPushButton *delete_button;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *ConditionModifierClass)
    {
        if (ConditionModifierClass->objectName().isEmpty())
            ConditionModifierClass->setObjectName(QString::fromUtf8("ConditionModifierClass"));
        ConditionModifierClass->resize(856, 257);
        verticalLayout_2 = new QVBoxLayout(ConditionModifierClass);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        widget = new QWidget(ConditionModifierClass);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        button_group_container = new QWidget(widget);
        button_group_container->setObjectName(QString::fromUtf8("button_group_container"));

        horizontalLayout->addWidget(button_group_container);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        add_button = new QPushButton(widget);
        add_button->setObjectName(QString::fromUtf8("add_button"));
        add_button->setMaximumSize(QSize(70, 1000));

        verticalLayout->addWidget(add_button);

        delete_button = new QPushButton(widget);
        delete_button->setObjectName(QString::fromUtf8("delete_button"));
        delete_button->setMaximumSize(QSize(70, 16777215));

        verticalLayout->addWidget(delete_button);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_2->addWidget(widget);


        retranslateUi(ConditionModifierClass);

        QMetaObject::connectSlotsByName(ConditionModifierClass);
    } // setupUi

    void retranslateUi(QWidget *ConditionModifierClass)
    {
        ConditionModifierClass->setWindowTitle(QApplication::translate("ConditionModifierClass", "ConditionModifier", nullptr));
        add_button->setText(QApplication::translate("ConditionModifierClass", "\346\267\273\345\212\240", nullptr));
        delete_button->setText(QApplication::translate("ConditionModifierClass", "\345\210\240\351\231\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConditionModifierClass: public Ui_ConditionModifierClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONDITIONMODIFIER_H
