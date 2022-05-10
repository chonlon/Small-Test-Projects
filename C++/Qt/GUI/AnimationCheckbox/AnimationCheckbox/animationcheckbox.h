#ifndef ANIMATIONCHECKBOX_H
#define ANIMATIONCHECKBOX_H

#include <QWidget>

namespace Ui {
class AnimationCheckbox;
}

class QState;
class QStateMachine;
class QSignalTransition;

class AnimationCheckbox : public QWidget
{
    Q_OBJECT

public:
    explicit AnimationCheckbox(QWidget *parent = 0);
    ~AnimationCheckbox();

private:
    Ui::AnimationCheckbox *ui;

    QStateMachine* state_machine_p_{nullptr};
    QSignalTransition* checked_transition_p_{nullptr};
    QSignalTransition* unchecked_transition_p_{nullptr};
};

#endif // ANIMATIONCHECKBOX_H
