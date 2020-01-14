#pragma once

#include "TypeSelector.h"
#include <QLineEdit>

class AddTypeSelector : public TypeSelector
{
public:
    AddTypeSelector(QWidget* parent);
    ~AddTypeSelector() override;

    QString getTypeName() const;
private:
    QHBoxLayout name_layout_;
    QLabel name_reminder_;
    QLineEdit name_edit_;
};
