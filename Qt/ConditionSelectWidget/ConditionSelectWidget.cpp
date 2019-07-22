#include "ConditionSelectWidget.h"
#include "ui_ConditionSelectWidget.h"
#include <QVBoxLayout>
#include <QListView>
#include <QPushButton>

using Ui::Form;

class ConditionWidget : public QWidget {
public:
    ConditionWidget(QWidget *parent = nullptr) : QWidget(parent), ui(new Form{}) {
        ui->setupUi(this);
    }
    Form* ui;
};

struct ConditionSelectWidgetPrivate {
    ConditionSelectWidgetPrivate() : middle_widget(nullptr), middle_widget_layout(nullptr), picname_result_view(nullptr), add_condition_button(nullptr) {}

    QWidget* middle_widget;
    QVBoxLayout *middle_widget_layout;
    QListView *picname_result_view;
    QPushButton *add_condition_button;

    QVBoxLayout* layout;
};

ConditionSelectWidget::ConditionSelectWidget(QWidget *parent) :
    QWidget(parent)
{
    data_ = new ConditionSelectWidgetPrivate{};

    data_->middle_widget = new QWidget{this};
    auto condition_widget = new ConditionWidget{data_->middle_widget};
    data_->layout = new QVBoxLayout{this};
    data_->add_condition_button = new QPushButton{this};
    data_->picname_result_view = new QListView{this};
    data_->middle_widget_layout = new QVBoxLayout{data_->middle_widget};

    data_->middle_widget_layout->addWidget(condition_widget);
    data_->layout->addWidget(data_->middle_widget);
    data_->layout->addWidget(data_->add_condition_button);
    data_->layout->addWidget(data_->picname_result_view);

    connect(data_->add_condition_button, &QPushButton::clicked, [this]() {
        auto concition_widget = new ConditionWidget{data_->middle_widget};
        data_->middle_widget_layout->addWidget(concition_widget);
    });
    auto _condition_widget = new ConditionWidget{};
    _condition_widget->show();
}

ConditionSelectWidget::~ConditionSelectWidget()
{
}
