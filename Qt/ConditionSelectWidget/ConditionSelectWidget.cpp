#include "ConditionSelectWidget.h"
#include "ui_ConditionSelectWidget.h"
#include <QListView>
#include <QPushButton>
#include <QStandardItemModel>
#include <QVBoxLayout>

#include <QDebug>
using Ui::Form;

class ConditionWidget : public QWidget {
public:
    ConditionWidget(QStandardItemModel* defect_types_model,
        QWidget* parent = nullptr)
        : QWidget(parent)
        , ui(new Form{})
    {
        ui->setupUi(this);
        if (defect_types_model) {
            ui->comboBox->setModel(defect_types_model);
            ui->combo_box_2->setModel(defect_types_model);
            ui->combo_box_3->setModel(defect_types_model);
        }
    }
    Form* ui;
};

struct ConditionSelectWidgetPrivate {
    ConditionSelectWidgetPrivate()
        : middle_widget(nullptr)
        , middle_widget_layout(nullptr)
        , picname_result_view(nullptr)
        , add_condition_button(nullptr)
    {
    }

    QPushButton* filter_button;

    QWidget* middle_widget;
    QVBoxLayout* middle_widget_layout;
    // 用于展示筛选结果.
    QListView* picname_result_view;
    QPushButton* add_condition_button;

    // 用于设置所有的下拉选择框的缺陷类型的model.
    QStandardItemModel* defect_types_model;

    QVBoxLayout* layout;
};

ConditionSelectWidget::ConditionSelectWidget(QWidget* parent)
    : QWidget(parent)
{
    data_ = new ConditionSelectWidgetPrivate{};
    setupDefectTypesModel(QStringList{ "1", "2" });
    data_->middle_widget = new QWidget{ this };
    auto condition_widget = new ConditionWidget{ data_->defect_types_model, data_->middle_widget };
	initSpinBoxBignessLogic(condition_widget);

    data_->layout = new QVBoxLayout{ this };
    data_->add_condition_button = new QPushButton{ this };
    data_->filter_button = new QPushButton{ this };
    data_->picname_result_view = new QListView{ this };
    data_->middle_widget_layout = new QVBoxLayout{ data_->middle_widget };

    data_->middle_widget_layout->addWidget(condition_widget);
    data_->add_condition_button->setText(u8"添加条件");
    data_->layout->addWidget(data_->filter_button);
    data_->layout->addWidget(data_->middle_widget);
    data_->layout->addWidget(data_->add_condition_button);
    data_->layout->addWidget(data_->picname_result_view);

    connect(data_->add_condition_button, &QPushButton::clicked, [this]() {
        auto condition_widget = new ConditionWidget{ data_->defect_types_model, data_->middle_widget };
        data_->middle_widget_layout->addWidget(condition_widget);
    });
    connect(data_->filter_button, &QPushButton::clicked,
        [this]() { this->generateSqlQuery(); });
}

ConditionSelectWidget::~ConditionSelectWidget() {}

void ConditionSelectWidget::setupDefectTypesModel(const QStringList& list)
{
    data_->defect_types_model = new QStandardItemModel{ this };
    QList<QStandardItem*> item_list;
    for (const auto& name : list) {
        item_list << new QStandardItem{ name };
    }
    data_->defect_types_model->appendColumn(item_list);
}

// generate sql sequence by condition.
QString ConditionSelectWidget::generateSqlQuery()
{
    auto temp_func = [=](const ConditionWidget* widget) -> QString {
        auto chararr = "DefectName = %1 AND Area >= %2 AND Area <= %3 AND Contrast >= %4 AND Contrast <= %5 ";
        QString condition1{}, condition2{}, condition3{};
        if (widget->ui->group_box_1->isChecked()) {
            condition1
                .append("((")
                .append(
                    QString{ chararr }
                        .arg(widget->ui->comboBox->currentText())
                        .arg(widget->ui->spinbox_area_1_min->value())
                        .arg(widget->ui->spinbox_area_1_max->value())
                        .arg(widget->ui->spinbox_contrast_1_min->value())
                        .arg(widget->ui->spinbox_contrast_1_max->value()))
                .append(")");
        }
        if (widget->ui->group_box_2->isChecked()) {
            condition2
                .append(" AND (")
                .append(
                    QString{ chararr }
                        .arg(widget->ui->combo_box_2->currentText())
                        .arg(widget->ui->spinbox_area_2_min->value())
                        .arg(widget->ui->spinbox_area_2_max->value())
                        .arg(widget->ui->spinbox_contrast_2_min->value())
                        .arg(widget->ui->spinbox_contrast_2_max->value()))
                .append(")");
        }
        if (widget->ui->group_box_3->isChecked()) {
            condition3
                .append(" AND (")
                .append(
                    QString{ chararr }
                        .arg(widget->ui->combo_box_3->currentText())
                        .arg(widget->ui->spinbox_area_3_min->value())
                        .arg(widget->ui->spinbox_area_3_max->value())
                        .arg(widget->ui->spinbox_contrast_3_min->value())
                        .arg(widget->ui->spinbox_contrast_3_max->value()))
                .append("))");
        }
        QString result = QString{}.append(condition1).append(condition2).append(condition3);
        return result;
    };
    auto count = data_->middle_widget_layout->count();

    QString query{ "SELECT PicName FROM ListPicDefects " };
    for (auto i = 0; i < count; ++i) {
        auto widget = reinterpret_cast<ConditionWidget*>(
            data_->middle_widget_layout->itemAt(i)->widget());
        if (i == 0) {
            query.append("WHERE ").append(temp_func(widget));
        } else {
            query.append(" OR ").append(temp_func(widget));
        }
    }

    qDebug() << query;
    return query;
}

void ConditionSelectWidget::initSpinBoxBignessLogic(ConditionWidget const* widget)
{
    void (QDoubleSpinBox::*valueChanged)(double val) = &QDoubleSpinBox::valueChanged;
	// 两个对应的spinbox的逻辑关系绑定.
    auto singal_logic = [=](QDoubleSpinBox* min_spinbox, QDoubleSpinBox* max_spinbox) -> void {
        connect(min_spinbox,
            valueChanged,
            [=](double val) -> void {
                max_spinbox->setMinimum(val);
            });
        connect(max_spinbox,
            valueChanged,
            [=](double val) -> void {
                min_spinbox->setMaximum(val);
            });
    };
    singal_logic(widget->ui->spinbox_area_1_min, widget->ui->spinbox_area_1_max);
    singal_logic(widget->ui->spinbox_area_2_min, widget->ui->spinbox_area_2_max);
    singal_logic(widget->ui->spinbox_area_3_min, widget->ui->spinbox_area_3_max);
    singal_logic(widget->ui->spinbox_contrast_1_min, widget->ui->spinbox_contrast_1_max);
    singal_logic(widget->ui->spinbox_contrast_2_min, widget->ui->spinbox_contrast_2_max);
    singal_logic(widget->ui->spinbox_contrast_3_min, widget->ui->spinbox_contrast_3_max);
}