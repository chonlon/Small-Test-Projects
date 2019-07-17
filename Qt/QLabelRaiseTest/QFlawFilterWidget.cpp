#include "QFlawFilterWidget.h"
#include "QFlawSortFilterProxyModel.h"
#include "ui_QFlawFilterWidget.h"

#include <QAbstractItemModel>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QMap>
#include <QPushButton>
#include <QPair>
#include <QThread>
#include <QVBoxLayout>
#include <QVariant>
using Ui::UI;
class QFlawFilterBottomWidget : public QWidget {
public:
	QFlawFilterBottomWidget(QWidget* parent = nullptr) : QWidget(parent), ui(new UI{}) {
		ui->setupUi(this);
		ui->area_double_spinbox_max->setValue(100);
		ui->area_double_spinbox_max->setMinimum(0);
		ui->area_double_spinbox_min->setValue(0);
		ui->area_double_spinbox_min->setMaximum(100);

		ui->contrast_ratio_groupbox_spinbox_max->setValue(100);
		ui->contrast_ratio_groupbox_spinbox_max->setMinimum(0);
		ui->contrast_ratio_groupbox_spinbox_min->setValue(0);
		ui->contrast_ratio_groupbox_spinbox_min->setMaximum(100);
	}
	UI* ui;
};

/// <summary>
/// FlawSelectWidget类的所有私有数据, 编译防火墙.
/// </summary>
class QFlawFilterWidgetPrivate {
public:
	/*typedef QMap<QPushButton*, QAbstractItemModel*> ModelMap;*/
	// FIXME may use SortFilterModel directly.
	typedef QPair<QAbstractItemModel*, QFlawSortFilterProxyModel*> ModelPair;
	typedef QMap<QPushButton*, ModelPair> ModelMap;
	QFlawFilterWidgetPrivate() : button_group(nullptr), top_layout(nullptr), layout(nullptr) {}
	~QFlawFilterWidgetPrivate() {
		delete top_layout;
		delete button_group;
	}
	QFlawFilterBottomWidget* bottom_widget;
	QButtonGroup* button_group;
	QHBoxLayout* top_layout;
	QVBoxLayout* layout;
	ModelMap model_map;
};

QFlawFilterWidget::QFlawFilterWidget(QWidget* parent /*= nullptr*/) : QWidget(parent) {
	m_data = new QFlawFilterWidgetPrivate{};

	initButtonGroup();

	m_data->bottom_widget = new QFlawFilterBottomWidget{ this };
	// tabelView 不允许编辑.
	m_data->bottom_widget->ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

	initLayout();
	initConnect();
}

QFlawFilterWidget::~QFlawFilterWidget() {
	delete m_data;
}

Q_INVOKABLE void QFlawFilterWidget::onButtonClicked() {
	auto sender_button = static_cast<QPushButton*>(sender());
	//筛选
	if (sender_button == m_data->bottom_widget->ui->filter_button) {
		double _min, _max;
		if (m_data->bottom_widget->ui->area_groupbox->isChecked()) {
			_min = m_data->bottom_widget->ui->area_double_spinbox_min->value();
			_max = m_data->bottom_widget->ui->area_double_spinbox_max->value();
		}
		else {
			_min = m_data->bottom_widget->ui->contrast_ratio_groupbox_spinbox_min->value();
			_max = m_data->bottom_widget->ui->contrast_ratio_groupbox_spinbox_max->value();
		}
		m_data->model_map[static_cast<QPushButton*>(m_data->button_group->checkedButton())]
			.second->setFilter(_min, _max);
	}
	else { //点击按钮组里面的按钮之一
		// HACK model pointer may be null.need a check?
		m_data->bottom_widget->ui->tableView->setModel(m_data->model_map[sender_button].second);
	}
}

void QFlawFilterWidget::initButtonGroup() {
	m_data->button_group = new QButtonGroup{};

	QStringList flaw_list;
	flaw_list << QString::fromLocal8Bit("白点") << QString::fromLocal8Bit("裂缝");
	for (auto i = 0; i < flaw_list.length(); ++i) {
		auto button = new QPushButton{ flaw_list.at(i), this };
		button->setCheckable(true);
		// FIXME delete model, use filter_model directly.
		auto model = getModelByName(flaw_list.at(i));
		auto filter_model = new QFlawSortFilterProxyModel();
		filter_model->setSourceModel(model);
		m_data->model_map[button] = QFlawFilterWidgetPrivate::ModelPair(model, filter_model);
		button->setProperty("class", "Group Button");
		connect(button, &QPushButton::clicked, this, &QFlawFilterWidget::onButtonClicked);
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

void QFlawFilterWidget::initLayout() {
	m_data->layout = new QVBoxLayout{ this };
	m_data->layout->addLayout(m_data->top_layout);
	m_data->layout->addWidget(m_data->bottom_widget);
}

void QFlawFilterWidget::initConnect() {
	connect(m_data->bottom_widget->ui->filter_button,
		&QPushButton::clicked,
		this,
		&QFlawFilterWidget::onButtonClicked);

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

	// 由于valueChanged有重载, 所以得这么写.
	void (QDoubleSpinBox::*valueChanged)(double val) = &QDoubleSpinBox::valueChanged;
	connect(m_data->bottom_widget->ui->area_double_spinbox_min,
		valueChanged,
		[this](double val) -> void {
		m_data->bottom_widget->ui->area_double_spinbox_max->setMinimum(val);
	});
	connect(m_data->bottom_widget->ui->area_double_spinbox_max,
		valueChanged,
		[this](double val) -> void {
		m_data->bottom_widget->ui->area_double_spinbox_min->setMaximum(val);
	});
	connect(m_data->bottom_widget->ui->contrast_ratio_groupbox_spinbox_min,
		valueChanged,
		[this](double val) -> void {
		m_data->bottom_widget->ui->contrast_ratio_groupbox_spinbox_max->setMinimum(val);
	});
	connect(m_data->bottom_widget->ui->contrast_ratio_groupbox_spinbox_max,
		valueChanged,
		[this](double val) -> void {
		m_data->bottom_widget->ui->contrast_ratio_groupbox_spinbox_min->setMaximum(val);
	});
}

QAbstractItemModel* QFlawFilterWidget::getModelByName(const QString& name) {
	//FIXME return true data.
	return nullptr;
}