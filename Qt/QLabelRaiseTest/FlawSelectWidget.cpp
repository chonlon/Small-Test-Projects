#include "FlawSelectWidget.h"
#include "ui_FlawSelectWidget.h"

#include <QButtonGroup>
#include <QPushButton>
#include <QVariant>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QThread>
using Ui::FlawSelectWidgetBottom;
class FlawSelectWidgetBottomWidget : public QWidget {
public:
	FlawSelectWidgetBottomWidget(QWidget *parent = nullptr) : QWidget(parent), ui(new FlawSelectWidgetBottom{}) {
		ui->setupUi(this);
	}
	FlawSelectWidgetBottom *ui;
};


///// <summary>
///// FlawSelectWidget类的所有私有数据, 编译防火墙.
///// </summary>
class FlawSelectWidgetPrivate {
public:
    FlawSelectWidgetPrivate() : button_group(nullptr), top_layout(nullptr), layout(nullptr) {}
    ~FlawSelectWidgetPrivate() {
        delete top_layout;
        delete button_group;
    }
    FlawSelectWidgetBottomWidget *bottom_widget;
    QButtonGroup *button_group;
    QHBoxLayout *top_layout;
    QVBoxLayout *layout;
};


FlawSelectWidget::FlawSelectWidget(QWidget *parent /*= nullptr*/) : QWidget(parent)
{
	m_data = new FlawSelectWidgetPrivate{};
	m_data->button_group = new QButtonGroup{};
    QStringList flaw_list;
    flaw_list << QString::fromLocal8Bit("白点")
        << QString::fromLocal8Bit("裂缝");
    for (auto i = 0; i < flaw_list.length(); ++i) {
        auto button = new QPushButton{ flaw_list.at(i), this };
        button->setCheckable(true);
        button->setProperty("class", "Group Button");
        m_data->button_group->addButton(button);
    }
    if (!m_data->button_group->buttons().empty()) {
        m_data->button_group->buttons().at(0)->setChecked(true);
    }
    m_data->top_layout = new QHBoxLayout{};
    for (auto i : m_data->button_group->buttons()) {
        m_data->top_layout->addWidget(i);
    }

	m_data->bottom_widget = new FlawSelectWidgetBottomWidget{ this };
	m_data->layout = new QVBoxLayout{ this };
	m_data->layout->addLayout(m_data->top_layout);
	m_data->layout->addWidget(m_data->bottom_widget);

	connect(m_data->bottom_widget->ui->groupBox, &QGroupBox::clicked, [this]() {
		m_data->bottom_widget->ui->groupBox_2->setChecked(false);

		if (!m_data->bottom_widget->ui->groupBox->isChecked()) {
			m_data->bottom_widget->ui->groupBox->setChecked(true);
		}
	});
	connect(m_data->bottom_widget->ui->groupBox_2, &QGroupBox::clicked, [this]() {
		m_data->bottom_widget->ui->groupBox->setChecked(false);
		if (!m_data->bottom_widget->ui->groupBox_2->isChecked()) {
			m_data->bottom_widget->ui->groupBox_2->setChecked(true);
		}
	});
}


FlawSelectWidget::~FlawSelectWidget()
{
    delete m_data;
}
