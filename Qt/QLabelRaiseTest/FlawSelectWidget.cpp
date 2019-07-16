#include "FlawSelectWidget.h"
#include "ui_FlawSelectWidget.h"

#include <QButtonGroup>
#include <QPushButton>
#include <QVariant>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QThread>
#include <QMap>
#include <QAbstractItemModel>
using Ui::FlawSelectWidgetBottom;
class FlawSelectWidgetBottomWidget : public QWidget {
public:
	FlawSelectWidgetBottomWidget(QWidget *parent = nullptr) : QWidget(parent), ui(new FlawSelectWidgetBottom{}) {
		ui->setupUi(this);
	}
	FlawSelectWidgetBottom *ui;
};

/// <summary>
/// FlawSelectWidget类的所有私有数据, 编译防火墙.
/// </summary>
class FlawSelectWidgetPrivate {
public:
	typedef QMap<QPushButton*, QAbstractItemModel*> ModelMap;
	FlawSelectWidgetPrivate() : button_group(nullptr), top_layout(nullptr), layout(nullptr) {}
	~FlawSelectWidgetPrivate() {
		delete top_layout;
		delete button_group;
	}
	FlawSelectWidgetBottomWidget *bottom_widget;
	QButtonGroup *button_group;
	QHBoxLayout *top_layout;
	QVBoxLayout *layout;
	ModelMap model_map;
};

FlawSelectWidget::FlawSelectWidget(QWidget *parent /*= nullptr*/) : QWidget(parent)
{
	m_data = new FlawSelectWidgetPrivate{};
	
	initButtonGroup();

	m_data->bottom_widget = new FlawSelectWidgetBottomWidget{ this };

	initLayout();
	initConnect();
}

FlawSelectWidget::~FlawSelectWidget()
{
	delete m_data;
}

Q_INVOKABLE void FlawSelectWidget::onButtonClicked()
{
	auto sender_button = static_cast<QPushButton*>(sender());
	if (sender_button == m_data->bottom_widget->ui->filter_button) {
		// #fix here
		// emit filter();
	}
	else {
		// #fix model pointer may be null.need a check?
		m_data->bottom_widget->ui->tableView->setModel(m_data->model_map[sender_button]);
	}
}

void FlawSelectWidget::initButtonGroup()
{
	m_data->button_group = new QButtonGroup{};

	QStringList flaw_list;
	flaw_list << QString::fromLocal8Bit("白点")
		<< QString::fromLocal8Bit("裂缝");
	for (auto i = 0; i < flaw_list.length(); ++i) {
		auto button = new QPushButton{ flaw_list.at(i), this };
		button->setCheckable(true);
		// #fix here, need a true model pointer.
		m_data->model_map[button] = nullptr;
		button->setProperty("class", "Group Button");
		connect(button, &QPushButton::clicked, this, &FlawSelectWidget::onButtonClicked);
		m_data->button_group->addButton(button);
	}
	if (!m_data->button_group->buttons().empty()) {
		m_data->button_group->buttons().at(0)->setChecked(true);
	}
	m_data->top_layout = new QHBoxLayout{};
	for (auto i : m_data->button_group->buttons()) {
		m_data->top_layout->addWidget(i);
	}
}

void FlawSelectWidget::initLayout()
{
	m_data->layout = new QVBoxLayout{ this };
	m_data->layout->addLayout(m_data->top_layout);
	m_data->layout->addWidget(m_data->bottom_widget);
}

void FlawSelectWidget::initConnect()
{
	connect(m_data->bottom_widget->ui->filter_button, &QPushButton::clicked, this, &FlawSelectWidget::onButtonClicked);

	connect(m_data->bottom_widget->ui->contrast_ratio_groupbox, &QGroupBox::clicked, [this]() {
		m_data->bottom_widget->ui->area_groupbox->setChecked(false);

		if (!m_data->bottom_widget->ui->contrast_ratio_groupbox->isChecked()) {
			m_data->bottom_widget->ui->contrast_ratio_groupbox->setChecked(true);
		}
	});
	connect(m_data->bottom_widget->ui->area_groupbox, &QGroupBox::clicked, [this]() {
		m_data->bottom_widget->ui->contrast_ratio_groupbox->setChecked(false);
		if (!m_data->bottom_widget->ui->area_groupbox->isChecked()) {
			m_data->bottom_widget->ui->area_groupbox->setChecked(true);
		}
	});
	void (QDoubleSpinBox::*valueChanged)(double val) = &QDoubleSpinBox::valueChanged;
	connect(m_data->bottom_widget->ui->area_double_spinbox_min, valueChanged, [this](double val)->void {
		m_data->bottom_widget->ui->area_double_spinbox_max->setMinimum(val);
	});
	connect(m_data->bottom_widget->ui->area_double_spinbox_max, valueChanged, [this](double val)->void {
		m_data->bottom_widget->ui->area_double_spinbox_min->setMaximum(val);
	});
	connect(m_data->bottom_widget->ui->contrast_ratio_groupbox_spinbox_min, valueChanged, [this](double val)->void {
		m_data->bottom_widget->ui->contrast_ratio_groupbox_spinbox_max->setMinimum(val);
	});
	connect(m_data->bottom_widget->ui->contrast_ratio_groupbox_spinbox_max, valueChanged, [this](double val)->void {
		m_data->bottom_widget->ui->contrast_ratio_groupbox_spinbox_min->setMaximum(val);
	});
}
