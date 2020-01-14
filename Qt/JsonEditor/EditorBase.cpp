#include "EditorBase.h"


EditorBase::EditorBase(QWidget* parent) : QWidget{nullptr}
{
    layout_.addWidget(&reminder_, 1);
}

void EditorBase::setReminder(const QString& string)
{
    reminder_.setText(string);
}

QString EditorBase::getReminderText() const
{
    return reminder_.text();
}

uint8_t EditorBase::getType() const
{
    return type_;
}

void EditorBase::emitModified()
{
    if (has_modified_) {
        emit modified();
        has_modified_ = false;
    }
}
