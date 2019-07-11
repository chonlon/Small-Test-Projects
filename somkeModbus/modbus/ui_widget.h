/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *modbus_init_btn;
    QPushButton *destroy_btn;
    QPushButton *start_read_btn;
    QPushButton *stop_read_btn;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QLabel *frame_rate;
    QSplitter *splitter;
    QPlainTextEdit *show_result;
    QPlainTextEdit *show_log;
    QSpacerItem *verticalSpacer;
    QPushButton *compress_btn;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(865, 483);
        verticalLayout = new QVBoxLayout(Widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        modbus_init_btn = new QPushButton(Widget);
        modbus_init_btn->setObjectName(QStringLiteral("modbus_init_btn"));

        horizontalLayout->addWidget(modbus_init_btn);

        destroy_btn = new QPushButton(Widget);
        destroy_btn->setObjectName(QStringLiteral("destroy_btn"));

        horizontalLayout->addWidget(destroy_btn);

        start_read_btn = new QPushButton(Widget);
        start_read_btn->setObjectName(QStringLiteral("start_read_btn"));

        horizontalLayout->addWidget(start_read_btn);

        stop_read_btn = new QPushButton(Widget);
        stop_read_btn->setObjectName(QStringLiteral("stop_read_btn"));

        horizontalLayout->addWidget(stop_read_btn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_2 = new QLabel(Widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        frame_rate = new QLabel(Widget);
        frame_rate->setObjectName(QStringLiteral("frame_rate"));

        horizontalLayout->addWidget(frame_rate);


        verticalLayout->addLayout(horizontalLayout);

        splitter = new QSplitter(Widget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        show_result = new QPlainTextEdit(splitter);
        show_result->setObjectName(QStringLiteral("show_result"));
        splitter->addWidget(show_result);
        show_log = new QPlainTextEdit(splitter);
        show_log->setObjectName(QStringLiteral("show_log"));
        splitter->addWidget(show_log);

        verticalLayout->addWidget(splitter);

        verticalSpacer = new QSpacerItem(843, 204, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        compress_btn = new QPushButton(Widget);
        compress_btn->setObjectName(QStringLiteral("compress_btn"));

        verticalLayout->addWidget(compress_btn);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", Q_NULLPTR));
        modbus_init_btn->setText(QApplication::translate("Widget", "init", Q_NULLPTR));
        destroy_btn->setText(QApplication::translate("Widget", "destroy", Q_NULLPTR));
        start_read_btn->setText(QApplication::translate("Widget", "start", Q_NULLPTR));
        stop_read_btn->setText(QApplication::translate("Widget", "stop", Q_NULLPTR));
        label_2->setText(QApplication::translate("Widget", "\345\270\247\347\216\207\357\274\232", Q_NULLPTR));
        frame_rate->setText(QApplication::translate("Widget", "TextLabel", Q_NULLPTR));
        compress_btn->setText(QApplication::translate("Widget", "PushButton", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
