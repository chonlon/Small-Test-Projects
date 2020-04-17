#include "animationcheckbox.h"
#include "ui_animationcheckbox.h"
#include <QDebug>
#include <QDateTime>

AnimationCheckbox::AnimationCheckbox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnimationCheckbox)
{

    ui->setupUi(this);
    QLocale::setDefault(QLocale(QLocale::English, QLocale::UnitedStates));
    qDebug() << QDateTime::currentDateTime().toLocalTime().toString(Qt::TextDate);
}

AnimationCheckbox::~AnimationCheckbox()
{
    delete ui;
}
