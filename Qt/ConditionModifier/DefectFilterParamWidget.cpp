#include "DefectFilterParamWidget.h"
#include "ui_ConditionModifier.h"
#include <QGridLayout>
#include <QDebug>
#include <QPushButton>
#include <qbuttongroup.h>
constexpr auto default_defect_name = u8"新缺陷";

/***********************************************************/
// Ui Widgets                                              //
/***********************************************************/
class AlgoSelector : public QWidget
{
};

class ConditionContainer : public QWidget
{
};

/***********************************************************/
// Impl                                                    //
/***********************************************************/
struct DefectFilterParamWidget::Impl
{
	Impl(QWidget* parent)
	{
		parent_ = parent;
		ui->setupUi(parent);
		buttons_layout = new QGridLayout{ ui->button_group_container };
	};

	~Impl()
	{
	}

	void addCondition(uint8_t row, uint8_t column);
	bool deleteCondition(uint8_t row, uint8_t column);
	bool deleteConditionRow(int row);
	void addDefect(const QString& name);
	void addEmptyDefect();
	void deleteCurrentDefect();
	void setDefects(const QVector<QString>& defect_names);

	QScopedPointer<QButtonGroup> button_group{new QButtonGroup{}};
	QGridLayout* buttons_layout{nullptr};

	// button's id map to container.
	QMap<int, ConditionContainer*> button_to_container;
	QVector<QPushButton*> buttons;
	Ui::ConditionModifierClass* ui{ new Ui::ConditionModifierClass };
private:
	const char* id = "Id";
	// 当前buttongroup中的应该添加的id, 使用这个属性的原因是button可能被删除再添加, 那么button id如果按照button的数量来算的话会重复. 如果每次去删都去遍历一遍又太麻烦了.
	QWidget* parent_{nullptr};
};

void DefectFilterParamWidget::Impl::addCondition(uint8_t row, uint8_t column)
{

}

bool DefectFilterParamWidget::Impl::deleteCondition(uint8_t row, uint8_t column)
{
	return false;
}

bool DefectFilterParamWidget::Impl::deleteConditionRow(int row)
{
	return false;
}

void DefectFilterParamWidget::Impl::addDefect(const QString& name)
{
	auto button = new QPushButton{ name };
	button->setCheckable(true);
	button_group->addButton(button);

	auto button_count = button_group->buttons().size() - 1;
	button->setProperty(id, button_count);
	buttons_layout->addWidget(button, button_count / 10, button_count % 10);
	buttons.push_back(button);
}

void DefectFilterParamWidget::Impl::addEmptyDefect()
{
	static int i = 0;
	addDefect(QString{ default_defect_name }.append(QString::number(++i)));
}

void DefectFilterParamWidget::Impl::deleteCurrentDefect()
{
	auto button = button_group->checkedButton();


	//buttons_layout = new QGridLayout{ ui->button_group_container };
	//ui->button_group_container->setLayout(buttons_layout);
	auto index = button->property(id).toInt();

	auto button_count = 0;
	for (auto _button : buttons) {
		qDebug() << _button->property(id).toString();
	}

	auto size = buttons.size();
	for (int i = size - 1; i > index; --i) {
		qDebug() << buttons.at(i - 1)->property(id).toString() << "---" << buttons.at(i)->property(id).toString();
		buttons_layout->replaceWidget(buttons.at(i - 1), buttons.at(i));
	}
	button_group->removeButton(button);
	buttons.remove(index);
	for(auto _button : buttons) {
	    qDebug() << _button->property(id).toString();
		_button->setProperty(id, button_count);
		++button_count;
	}
	delete button;
}

void DefectFilterParamWidget::Impl::setDefects(const QVector<QString>& defect_names)
{
	button_group.reset(new QButtonGroup{});

	for (auto name : defect_names) {
		addDefect(name);
	}
	if (!button_group->buttons().empty()) {
		button_group->buttons().at(0)->setChecked(true);
	}
}




/***********************************************************/
// ConditionModifier                                       //
/***********************************************************/
DefectFilterParamWidget::DefectFilterParamWidget(QWidget* parent)
	: QWidget(parent)
{
	impl_ = new Impl{this};
	setDefects(QVector<QString>{"123", "hhh"});
	connect(impl_->ui->add_button, &QPushButton::clicked, this, &DefectFilterParamWidget::addEmptyDefect);
	connect(impl_->ui->delete_button, &QPushButton::clicked, this, &DefectFilterParamWidget::deleteCurrentDefect);
}

void DefectFilterParamWidget::addCondition(uint8_t row, uint8_t column)
{
	impl_->addCondition(row, column);
}

bool DefectFilterParamWidget::deleteCondition(uint8_t row, uint8_t column)
{
	return impl_->deleteCondition(row, column);
}

bool DefectFilterParamWidget::deleteConditionRow(int row)
{
	return impl_->deleteConditionRow(row);
}

void DefectFilterParamWidget::addDefect(const QString& name)
{
	impl_->addDefect(name);
}


void DefectFilterParamWidget::setDefects(const QVector<QString>& defect_names)
{
	impl_->setDefects(defect_names);
}

void DefectFilterParamWidget::addEmptyDefect()
{
	impl_->addEmptyDefect();
}

void DefectFilterParamWidget::deleteCurrentDefect()
{
	impl_->deleteCurrentDefect();
}

// void ConditionModifier::conditionAdded()
// {
//     impl_->conditionAdded();
// }
//
// void ConditionModifier::conditionDeleted(uint8_t row, uint8_t column)
// {
// }
