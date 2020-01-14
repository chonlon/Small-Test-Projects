#pragma once
#include "EditorBase.h"

class EditorFactory
{
public:
    EditorFactory()  = default;
    ~EditorFactory() = default;

    enum EditorType : uint8_t { IntSpinBox, DoubleSpinBox, DirEditor, LineEditor, FileNameEditor };

    static EditorBase* getEditor(EditorType type, QWidget* parent);
    static QString getTypeString(EditorType type);
};
