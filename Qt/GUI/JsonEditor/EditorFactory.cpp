#include "EditorFactory.h"
#include <QDebug>
#include "EditorDerived.h"


EditorBase* EditorFactory::getEditor(EditorType type, QWidget* parent)
{
    switch (type) {
    case IntSpinBox:
        return new ::IntSpinBox{parent};
    case DoubleSpinBox:
        return new ::DoubleSpinBox{parent};
    case DirEditor:
        return new ::DirEditor{parent};
    case LineEditor:
        return new ::LineEditor{parent};
    case FileNameEditor:
        return new ::FileNameEditor{parent};
    default:
        qWarning() << "request wrong type!";
        return nullptr;
    }
}

QString EditorFactory::getTypeString(EditorType type)
{
    switch (type) {
    case IntSpinBox:
        return "int";
    case DoubleSpinBox:
        return "double";
    case DirEditor:
        return "dir";
    case LineEditor:
        return "string";
    case FileNameEditor:
        return "file";
    default:
        qWarning() << "request wrong type!";
        return "";
    }
}
