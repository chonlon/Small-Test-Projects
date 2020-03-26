#ifndef ANIMATIONCHECKBOX_H
#define ANIMATIONCHECKBOX_H

#include <QWidget>

namespace Ui {
class AnimationCheckbox;
}

class AnimationCheckbox : public QWidget
{
    Q_OBJECT

public:
    explicit AnimationCheckbox(QWidget *parent = 0);
    ~AnimationCheckbox();

private:
    Ui::AnimationCheckbox *ui;
};

#endif // ANIMATIONCHECKBOX_H
