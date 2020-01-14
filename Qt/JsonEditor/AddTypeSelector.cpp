#include "AddTypeSelector.h"
#include "ui_TypeSelector.h"


AddTypeSelector::AddTypeSelector(QWidget* parent) : TypeSelector{parent}
{
    name_reminder_.setText(u8"属性名：");
    name_layout_.addWidget(&name_reminder_, 1);
    name_layout_.addWidget(&name_edit_, 2);
    name_layout_.setContentsMargins(10, 0, 10, 0);
    ui_->verticalLayout->insertLayout(0, &name_layout_);
}


AddTypeSelector::~AddTypeSelector()
{
}

QString AddTypeSelector::getTypeName() const
{
    return name_edit_.text();
}
