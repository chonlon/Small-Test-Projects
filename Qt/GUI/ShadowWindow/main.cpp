#include "dialog.h"

#include <QDebug>
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);


    QPushButton *quitButton = new QPushButton("exit");
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(new QLabel("drop to move"));

    layout->addWidget(quitButton);

    QWidget *contentWidget = new QWidget();
    contentWidget->setLayout(layout);
    contentWidget->setObjectName("contentWidget");
    contentWidget->setStyleSheet("#contentWidget{background: white; border-radius: 4px;}" // 定制圆角
                                 ".QLabel{background: gray;}.QTextEdit{background: white;}");

    QObject::connect(quitButton, &QPushButton::clicked, [&app] {
        app.quit();
    });


    FramelessWindow *window = new FramelessWindow(contentWidget);
    window->resize(300, 400);
    window->show();

    return app.exec();
}
