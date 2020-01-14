#include "TypeSelector.h"
#include "ui_TypeSelector.h"
#include <QDebug>

TypeSelector::TypeSelector(QWidget* parent)
    : QDialog(parent)
{
    ui_ = new Ui::TypeSelector();
    ui_->setupUi(this);

    ui_->comboBox->insertItem(EditorFactory::IntSpinBox, u8"整数类型");
    ui_->comboBox->insertItem(EditorFactory::DoubleSpinBox, u8"小数类型");
    ui_->comboBox->insertItem(EditorFactory::LineEditor, u8"文本类型");
    ui_->comboBox->insertItem(EditorFactory::DirEditor, u8"路径");

    spin_box_->setReminder(u8"请输入属性值：");
    double_spin_box_->setReminder(u8"请输入属性值：");
    line_edit_->setReminder(u8"请输入属性值：");
    dir_edit_->setReminder(u8"请输入属性值：");

    ui_->stackedWidget->insertWidget(EditorFactory::IntSpinBox, spin_box_);
    ui_->stackedWidget->insertWidget(EditorFactory::DoubleSpinBox, double_spin_box_);
    ui_->stackedWidget->insertWidget(EditorFactory::DirEditor, dir_edit_);
    ui_->stackedWidget->insertWidget(EditorFactory::LineEditor, line_edit_);
    ui_->stackedWidget->setCurrentIndex(0);

    connect(ui_->okButton, &QPushButton::clicked, this, &TypeSelector::onOkClicked);
    connect(ui_->cancelButton, &QPushButton::clicked, this, &TypeSelector::onCancelClicked);

    connect(ui_->comboBox,
            static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            [this](int index) {
                setCurrentValue(qMakePair(index, QVariant{}));
            });
}

TypeSelector::~TypeSelector()
{
    delete ui_;
}

QPair<uint8_t, QVariant> TypeSelector::getValue() const
{
    return qMakePair(type_, value_);
}

void TypeSelector::setCurrentValue(QPair<uint8_t, QVariant> value)
{
    ui_->comboBox->setCurrentIndex(value.first);
    ui_->stackedWidget->setCurrentIndex(value.first);
    switch (value.first) {
    case EditorFactory::IntSpinBox:
        spin_box_->setValue(value.second);
        break;
    case EditorFactory::DoubleSpinBox:
        double_spin_box_->setValue(value.second);
        break;
    case EditorFactory::LineEditor:
        line_edit_->setValue(value.second);
        break;
    case EditorFactory::DirEditor:
        dir_edit_->setValue(value.second);
        break;
    default:
        qWarning() << "request wrong type!";
        break;
    }
}

void TypeSelector::onOkClicked()
{
    type_ = ui_->comboBox->currentIndex();

    switch (type_) {
    case EditorFactory::IntSpinBox:
        value_ = spin_box_->getValue();
        break;
    case EditorFactory::DoubleSpinBox:
        value_ = double_spin_box_->getValue();
        break;
    case EditorFactory::LineEditor:
        value_ = line_edit_->getValue();
        break;
    case EditorFactory::DirEditor:
        value_ = dir_edit_->getValue();
        break;
    default:
        qWarning() << "request wrong type!";
        break;
    }

    this->accept();
    emit okButtonClicked();
}

void TypeSelector::onCancelClicked()
{
    this->reject();
    emit cancelClicked();
}
