#include "animationcheckbox.h"
#include "ui_animationcheckbox.h"

AnimationCheckbox::AnimationCheckbox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnimationCheckbox)
{
    ui->setupUi(this);
}

AnimationCheckbox::~AnimationCheckbox()
{
    delete ui;
}
