#include "DefectFilterParamWidget.h"
#include "ui_ConditionModifier.h"
#include "ui_ConditionSelectWidget.h"
#include "DbCLineEdit.h"
#include <QGridLayout>
#include <QDebug>
#include <QComboBox>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QStackedWidget>
constexpr auto default_defect_name = u8"新缺陷";
constexpr auto condition_height    = 130;
constexpr auto condition_spacing   = 5;
// todo list:
// 1. 按钮单击事件
// 2. 按钮双击事件
// 3. 所有需要@lou添加的都添加了fixme标签.

/***********************************************************/
// Ui Widgets                                              //
/***********************************************************/
/// <summary>
/// 单行条件的条件框
/// </summary>
class ConditionWidget final : public QWidget
{
public:
    explicit ConditionWidget(QWidget* parent = nullptr)
        : QWidget(parent)
        , ui(new Ui::Form{})
    {
        ui->setupUi(this);
        contents_layout = new QHBoxLayout{ui->condition_contents};
        contents_layout->setContentsMargins(0, 0, 0, 0);
        ui->scrollAreaWidgetContents->layout()->setContentsMargins(0, 0, 0, 0);
        this->setFixedHeight(condition_height);
    }

public:
    Ui::Form* ui;
    QHBoxLayout* contents_layout;
};

/// <summary>
/// 单个条件的条件框.
/// </summary>
class SingleCondition final : public QWidget
{
    // Q_OBJECT
public:
    SingleCondition(QWidget* parent = nullptr)
        : QWidget(parent)
        , combo_box(nullptr)
        , label_max(nullptr)
        , label_min(nullptr)
        , max_spinbox(nullptr)
        , min_spinbox(nullptr)
        , layout(nullptr)
    {
    }

public:
    QComboBox* combo_box;
    QPushButton* close_button;
    QLabel* label_max;
    QLabel* label_min;
    QDoubleSpinBox* max_spinbox;
    QDoubleSpinBox* min_spinbox;
    QGridLayout* layout;
};

class AlgoSelector final : public QWidget
{
public:
    explicit AlgoSelector(QWidget* parent) : QWidget{parent}
    {
        layout = new QVBoxLayout{this};
    }

    QVBoxLayout* layout;
    QVector<QPair<QString, QCheckBox*>> algos;
};

class ConditionContainer final : public QWidget
{
public:
    explicit ConditionContainer(QWidget* parent) : QWidget{parent}
    {
        layout = new QVBoxLayout{this};
    }

    QVector<ConditionWidget*> condition_widgets;
    QVBoxLayout* layout;
};

class Container final : public QWidget
{
public:
    explicit Container(QWidget* parent) : QWidget{parent}
    {
        layout = new QVBoxLayout{this};

        scroll_area         = new QScrollArea{parent};
        condition_container = new ConditionContainer{scroll_area};
        scroll_area->setWidgetResizable(true);
        scroll_area->setWidget(condition_container);
        layout->addWidget(scroll_area);
        add_button = new QPushButton{u8"添加条件",this};
        layout->addWidget(add_button);
    }

    QVBoxLayout* layout;
    QScrollArea* scroll_area;
    ConditionContainer* condition_container;
    QPushButton* add_button;
};



/***********************************************************/
// Impl                                                    //
/***********************************************************/
struct DefectFilterParamWidget::Impl
{
    Impl(DefectFilterParamWidget* parent)
    {
        parent_ = parent;
        ui->setupUi(parent);
        ui->widget->setMaximumHeight(150);
        buttons_layout = new QGridLayout{ui->button_group_container};

        bottom_layout.reset(new QHBoxLayout{});
        algo_selector = new AlgoSelector{parent};
        //condition_container = new ConditionContainer{parent};
        //scroll_area         = new QScrollArea{condition_container};
        stacked_widget = new QStackedWidget{parent};

        bottom_layout->addWidget(algo_selector);
        bottom_layout->addWidget(stacked_widget);

        ui->main_layout->addLayout(bottom_layout.data());
    };

    ~Impl()
    {
    }

    // --defect groups--

    bool deleteSingleCondition(uint8_t row, uint8_t column);
    bool deleteConditionRow(int row);
    void addDefect(const QString& name);
    void addEmptyDefect();
    void deleteCurrentDefect();
    void setDefects(const QVector<QString>& defect_names);

    QScopedPointer<QButtonGroup> button_group{new QButtonGroup{}};
    QGridLayout* buttons_layout{nullptr};

    // button's id map to container.
    uint32_t current_button_id{0};
    QMap<int, Container*> id_to_container;
    QVector<QPushButton*> buttons;
    Ui::ConditionModifierClass* ui{new Ui::ConditionModifierClass};
    // --!defect groups--

    // --bottom ui--
    Container* newContainer();

    // new并初始化一个单个属性.
    SingleCondition* newSingleCondition(ConditionWidget* parent, int max, int min, QVector<QString>& strings);
    
    // 添加单个属性, 目前只能加到最后, column没有用.
    void addSingleCondition(uint8_t row, uint8_t column);

    // 添加单行属性
    void addConditionWidget();

    // 向界面中添加一个algo.
    void addAlgo(const QString& name);
    //将界面中的一个algo删除.
    void deleteAlgo(const QString& name);

    QScopedPointer<QHBoxLayout> bottom_layout;
    AlgoSelector* algo_selector;

    QStackedWidget* stacked_widget;
    // --!bottom ui--
private:
    const char* id = "Id";
    // 当前button group中的应该添加的id, 使用这个属性的原因是button可能被删除再添加, 那么button id如果按照button的数量来算的话会重复. 如果每次去删都去遍历一遍又太麻烦了.
    DefectFilterParamWidget* parent_{nullptr};
};

void DefectFilterParamWidget::Impl::addSingleCondition(uint8_t row, uint8_t column)
{
    auto id_num             = current_button_id;
    auto& condition_widgets = id_to_container[id_num]->condition_container->condition_widgets;

    auto size = condition_widgets.size();
    if (row > size + 1 || row < 1) return;
    if(row == size + 1) {
        addConditionWidget();
        row = size + 1;
    }
    condition_widgets[row - 1]->contents_layout->addWidget(newSingleCondition(condition_widgets[row - 1], 0, 999, QVector<QString>{}));
}

bool DefectFilterParamWidget::Impl::deleteSingleCondition(uint8_t row, uint8_t column)
{
    return false;
}

bool DefectFilterParamWidget::Impl::deleteConditionRow(int row)
{
    return false;
}

void DefectFilterParamWidget::Impl::addDefect(const QString& name)
{
    auto button = new QPushButton{name};
    auto container = newContainer();
    connect(container->add_button, &QPushButton::clicked, [container, this]() {
        //addSingleCondition(container->condition_container->condition_widgets.size(), 0);
        addConditionWidget();
        // fixme 添加单行条件按钮被按下.
    });
    
    stacked_widget->addWidget(container);

    connect(button, &QPushButton::clicked, [button, this]() {
        auto id_num = button->property(id).toInt();
        stacked_widget->setCurrentIndex(id_num);
        // fixme defect_button clicked.
        //bottom_layout->replaceWidget(id_to_container[current_button_id], id_to_container[id_num]);
        //current_button_id = id_num;
    });

    button->setCheckable(true);
    button_group->addButton(button);

    auto button_count = button_group->buttons().size() - 1;
    button->setProperty(id, button_count);
    id_to_container[button_count] = container;
    buttons_layout->addWidget(button, button_count / 10, button_count % 10);
    buttons.push_back(button);
}

void DefectFilterParamWidget::Impl::addEmptyDefect()
{
    static int i = 0;
    addDefect(QString{default_defect_name}.append(QString::number(++i)));
}

void DefectFilterParamWidget::Impl::deleteCurrentDefect()
{
    auto button = button_group->checkedButton();
    if (!button) return;
    

    //buttons_layout = new QGridLayout{ ui->button_group_container };
    //ui->button_group_container->setLayout(buttons_layout);
    auto index = button->property(id).toInt();

    auto button_count = 0;

    auto size = buttons.size();
    for (int i = size - 1; i > index; --i) {
        buttons_layout->replaceWidget(buttons.at(i - 1), buttons.at(i));
    }
    button_group->removeButton(button);
    stacked_widget->removeWidget(id_to_container[index]);
    delete id_to_container[index];
    buttons.remove(index);

    parent_->emitDefectDeleted(index);
    // 重排button的id属性.
    for (auto _button : buttons) {
        id_to_container[button_count] = id_to_container[_button->property(id).toInt()];
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

Container* DefectFilterParamWidget::Impl::newContainer()
{
    auto container = new Container{ parent_ };

    // fixme 是否需要添加一个空的条件窗口.
    return container;
}

SingleCondition* DefectFilterParamWidget::Impl::newSingleCondition(ConditionWidget* parent, int max, int min, QVector<QString>& strings)
{
    auto widget = new SingleCondition{parent};

    //widget->installEventFilter(this);

    widget->close_button = new QPushButton{u8"关闭", widget};
    widget->combo_box    = new QComboBox{widget};
    widget->layout       = new QGridLayout{widget};
    widget->label_min    = new QLabel{u8"最小值", widget};
    widget->label_max    = new QLabel{u8"最大值", widget};
    widget->min_spinbox  = new QDoubleSpinBox{widget};
    widget->max_spinbox  = new QDoubleSpinBox{widget};

    widget->close_button->setFixedSize(35, 25);
    widget->combo_box->setMaximumWidth(300);
    widget->min_spinbox->setMinimum(0);
    widget->min_spinbox->setMaximum(9999);
    widget->min_spinbox->setValue(min);
    widget->max_spinbox->setMaximum(9999);
    widget->max_spinbox->setMinimum(0);
    widget->max_spinbox->setValue(max);
    widget->layout->addWidget(widget->combo_box, 0, 0);
    widget->layout->addWidget(widget->close_button, 0, 1, Qt::AlignRight);
    widget->layout->addWidget(widget->label_min, 1, 0);
    widget->layout->addWidget(widget->min_spinbox, 1, 1);
    widget->layout->addWidget(widget->label_max, 2, 0);
    widget->layout->addWidget(widget->max_spinbox, 2, 1);
    widget->combo_box->addItems({u8"面积", u8"对比度", u8"长轴", u8"个数"});

    // todo install event filter
    //widget->min_spinbox->installEventFilter(this);
    //widget->max_spinbox->installEventFilter(this);
    //widget->combo_box->installEventFilter(this);

    void (QDoubleSpinBox::*valueChanged)(double val) = &QDoubleSpinBox::valueChanged;
    // 两个对应的spinbox的逻辑关系绑定.
    // fixme 这里是
    connect(widget->min_spinbox,
            valueChanged,
            [=](double val) -> void {
                widget->max_spinbox->setMinimum(val);
            });
    connect(widget->max_spinbox,
            valueChanged,
            [=](double val) -> void {
                widget->min_spinbox->setMaximum(val);
            });
    connect(widget->close_button,
            &QPushButton::clicked,
            [=]() {
                if (parent->contents_layout->count() < 2)
                    return;
                else
                    delete widget;
            });
    return widget;
}


void DefectFilterParamWidget::Impl::addConditionWidget()
{
    auto id_num = current_button_id;
    auto condition_container = id_to_container[id_num]->condition_container;
    auto widget = new ConditionWidget{condition_container};
    condition_container->layout->addWidget(widget);
    condition_container->condition_widgets.push_back(widget);

    if (!widget)
        return;


    widget->contents_layout->setContentsMargins(0, 0, 0, 0);
    // fixme 添加的单个框应该有选项(第四个参数不应该为空).
    widget->contents_layout->addWidget(newSingleCondition(widget, 999, 0, QVector<QString>{}));
    // 按值捕获了this和condition_widget指针.
    connect(widget->ui->close_button,
            &QPushButton::clicked,
            [=]() {
                // 删除一个condition widget, 减少最大高度.
                id_to_container[id_num]->scroll_area->setMaximumHeight(condition_container->condition_widgets.size() * (condition_height + condition_spacing) - condition_height);
                delete widget;
            });
    connect(widget->ui->add_button,
            &QPushButton::clicked,
            [=]() {
                
                //addSingleCondition(0, 0);
                // fixme 添加的单个框应该有选项(第四个参数不应该为空).
                widget->contents_layout->addWidget(newSingleCondition(widget, 999, 0, QVector<QString>{}));
            });
}

void DefectFilterParamWidget::Impl::addAlgo(const QString& name)
{
    QCheckBox* checkbox = new QCheckBox{algo_selector};

    connect(checkbox,
            &QCheckBox::stateChanged,
            [](int state) {
                // fixme 这个算法的checkbox对应的状态改变.
                if (state == Qt::Checked) {

                } else if (state == Qt::Unchecked) {

                }// else Qt::PartiallyChecked.
            });
    algo_selector->algos.push_back(qMakePair(name, checkbox));
}

void DefectFilterParamWidget::Impl::deleteAlgo(const QString& name)
{
    auto i = 0;
    for (auto v : algo_selector->algos) {
        if (v.first == name) {
            delete v.second;
            algo_selector->algos.remove(i);
            break;
        }
        ++i;
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
    impl_->addSingleCondition(row, column);
}

bool DefectFilterParamWidget::deleteCondition(uint8_t row, uint8_t column)
{
    return impl_->deleteSingleCondition(row, column);
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
