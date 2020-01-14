#pragma once
#include "EditorBase.h"
#include "EditorFactory.h"
#include <QSpinBox>
#include <QPushButton>
#include <QLineEdit>
#include <QFileDialog>
#include <QKeyEvent>
#include <QDebug>

class IntSpinBox final : public EditorBase
{
public:
    explicit IntSpinBox(QWidget* parent = nullptr) : EditorBase{parent}
    {
        type_ = EditorFactory::IntSpinBox;
        layout_.addWidget(&spin_box_, 2);
        connect(&spin_box_, &QSpinBox::editingFinished, this, &EditorBase::emitModified);
        connect(&spin_box_,
                static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
                [this]() {
                    if (!has_modified_) {
                        has_modified_ = true;
                        spin_box_.setStyleSheet("QSpinBox{border-color: rgb(255, 0, 0);}");
                    }
                });
        spin_box_.installEventFilter(this);
    }

    void setValue(const QVariant& val) override
    {
        has_modified_ = true;
        spin_box_.setValue(val.toInt());
        has_modified_ = false;
    }

    QVariant getValue() const override
    {
        return spin_box_.value();
    }

    void setNormal() override
    {
        spin_box_.setStyleSheet("QSpinBox{border-color: #9999999;}");
    }

protected:
    bool eventFilter(QObject* watched, QEvent* event) override
    {
        if (watched == &spin_box_ && event->type() == QEvent::KeyPress) {
            auto e = static_cast<QKeyEvent*>(event);
            if ((e->key() == Qt::Key_Enter) || (e->key() == Qt::Key_Return)) {
                emitModified();
                emit returnPressed();
                return true;
            }
        }
        return false;
    }

private:
    QSpinBox spin_box_;
};

class DoubleSpinBox final : public EditorBase
{
Q_OBJECT
public:
    explicit DoubleSpinBox(QWidget* parent = nullptr) : EditorBase{parent}
    {
        type_ = EditorFactory::DoubleSpinBox;
        layout_.addWidget(&double_spin_box_, 2);


        connect(&double_spin_box_, &QDoubleSpinBox::editingFinished, this, &DoubleSpinBox::editFinished);

        connect(&double_spin_box_,
                static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                [this]() {
                    if (!has_modified_) {
                        has_modified_ = true;
                        double_spin_box_.setStyleSheet("QDoubleSpinBox{border-color: rgb(255, 0, 0);}");
                    }
                });
        double_spin_box_.installEventFilter(this);
    }

    void setValue(const QVariant& val) override
    {
        has_modified_ = true;
        double_spin_box_.setValue(val.toDouble());
        has_modified_ = false;
    }

    QVariant getValue() const override
    {
        return double_spin_box_.value();
    }

    void setNormal() override
    {
        double_spin_box_.setStyleSheet("QDoubleSpinBox{border-color: #999999;}");
    }

protected:
    bool eventFilter(QObject* watched, QEvent* event) override
    {
        if (watched == &double_spin_box_ && event->type() == QEvent::KeyPress) {
            auto e = static_cast<QKeyEvent*>(event);
            if ((e->key() == Qt::Key_Enter) || (e->key() == Qt::Key_Return)) {
                emitModified();
                emit returnPressed();
                return true;
            }
        }
        return false;
    }

private:
    QDoubleSpinBox double_spin_box_;
};


class DirEditor : public EditorBase
{
public:
    explicit DirEditor(QWidget* parent = nullptr) : EditorBase{parent}
    {
        type_ = EditorFactory::DirEditor;

        layout_.addWidget(&edit_, 2);

        edit_layout_ = new QHBoxLayout{&edit_};
        button_      = new QPushButton{"", &edit_};
        button_->setCursor(Qt::ArrowCursor);
        button_->setFixedSize(25, 14);
        edit_layout_->setContentsMargins(0, 0, 0, 0);
        edit_layout_->addStretch();
        edit_layout_->addWidget(button_);

        edit_.setStyleSheet(QString{style_}.arg("#999999"));
        edit_.setGeometry(20, 20, 200, 26);

        edit_.setLayout(edit_layout_);


        connect(button_,
                &QPushButton::clicked,
                [this]() {
                    QString dir = QFileDialog::getExistingDirectory(this,
                                                                    tr(u8"选择路径"),
                                                                    edit_.text(),
                                                                    QFileDialog::ShowDirsOnly
                                                                    | QFileDialog::DontResolveSymlinks);
                    if (!dir.isEmpty()) {
                        has_modified_ =true;
                        emitModified();
                        edit_.setText(dir);
                    }
                });
        connect(&edit_, &QLineEdit::editingFinished, this, &EditorBase::emitModified);
        connect(&edit_,
                &QLineEdit::textChanged,
                [this]() {
                    if (!has_modified_) {
                        has_modified_ = true;
                        edit_.setStyleSheet(QString{style_}.arg("rgb(255, 0, 0)"));
                    }
                });
        connect(&edit_,
                &QLineEdit::returnPressed,
                [this]() {
                    emitModified();
                    emit returnPressed();
                });
    }

    void setValue(const QVariant& val) override
    {
        has_modified_ = true;
        edit_.setText(val.toString());
        has_modified_ = false;
    }

    QVariant getValue() const override
    {
        return edit_.text();
    }

    void setNormal() override
    {
        edit_.setStyleSheet(QString{style_}.arg("#999999"));
    }

protected:
    QPushButton* button_;
    QLineEdit edit_;
private:
    QHBoxLayout* edit_layout_;
    const char* style_ = "QLineEdit{border-color: %1;}\
                            QLineEdit QPushButton {\
                                margin-right: 2px;\
                                border: none;\
                                border-width: 0;\
                                border-image: url(:/Resources/power_input_24px_rounded.jpg) 0 0 0 0 stretch stretch;\
                            }\
                            QLineEdit QPushButton:hover:!pressed {\
                                border-image: url(:/Resources/power_input_24px_rounded_hover.jpg) 0 0 0 0 stretch stretch;\
                            }";
};

class FileNameEditor final : public DirEditor
{
public:
    explicit FileNameEditor(QWidget* parent) : DirEditor{parent}
    {
        type_ = EditorFactory::FileNameEditor;
        disconnect(button_, SIGNAL(clicked()), 0, 0);
        connect(button_,
                &QPushButton::clicked,
                [this]() {
                    QString file_name = QFileDialog::getOpenFileName(this,
                                                                     tr(u8"选择路径"),
                                                                     edit_.text(),
                                                                     "py file(*.py);;json file(*.json);;*"
                                                                    );
                    if (!file_name.isEmpty()) {
                        has_modified_ =true;
                        emitModified();
                        edit_.setText(file_name);
                    }
                        
                });
    }
};


class LineEditor final : public EditorBase
{
public:
    explicit LineEditor(QWidget* parent = nullptr) : EditorBase{parent}
    {
        type_ = EditorFactory::LineEditor;
        layout_.addWidget(&edit_, 2);
        connect(&edit_, &QLineEdit::editingFinished, this, &EditorBase::editFinished);
        connect(&edit_,
                &QLineEdit::textChanged,
                [this]() {
                    if (!has_modified_) {
                        has_modified_ = true;
                        edit_.setStyleSheet("QLineEdit{border-color: rgb(255, 0, 0);}");
                    }
                });

        connect(&edit_,
                &QLineEdit::returnPressed,
                [this]() {
                    emitModified();
                    emit returnPressed();
                });
    }

    void setValue(const QVariant& val) override
    {
        has_modified_ = true;
        edit_.setText(val.toString());
        has_modified_ = false;
    }

    QVariant getValue() const override
    {
        return edit_.text();
    }

    void setNormal() override
    {
        edit_.setStyleSheet("QLineEdit{border-color: #999999;}");
    }

private:
    QLineEdit edit_;
};
