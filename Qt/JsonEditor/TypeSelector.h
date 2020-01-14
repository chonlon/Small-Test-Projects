#pragma once

#include <QDialog>
#include "EditorFactory.h"
#include <QVariant>

namespace Ui
{
    class TypeSelector;
};

class TypeSelector : public QDialog
{
Q_OBJECT

public:
    TypeSelector(QWidget* parent = Q_NULLPTR);
    ~TypeSelector() override;

    QPair<uint8_t, QVariant> getValue() const;

    void setCurrentValue(QPair<uint8_t, QVariant> value);
private slots:
    void onOkClicked();
    void onCancelClicked();
signals:
    void okButtonClicked();
    void cancelClicked();
protected:
    Ui::TypeSelector* ui_;

private:


    uint8_t type_;
    QVariant value_;

    EditorBase* spin_box_{EditorFactory::getEditor(EditorFactory::IntSpinBox, this)};
    EditorBase* double_spin_box_{EditorFactory::getEditor(EditorFactory::DoubleSpinBox, this)};
    EditorBase* line_edit_{EditorFactory::getEditor(EditorFactory::LineEditor, this)};
    EditorBase* dir_edit_{EditorFactory::getEditor(EditorFactory::DirEditor, this)};
};
