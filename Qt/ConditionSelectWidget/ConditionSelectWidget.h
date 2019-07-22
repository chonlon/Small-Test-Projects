#ifndef CONDITIONSELECTWIDGET_H
#define CONDITIONSELECTWIDGET_H

#include <QWidget>

struct ConditionSelectWidgetPrivate;
class ConditionWidget;

class ConditionSelectWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ConditionSelectWidget(QWidget *parent = nullptr);
    ~ConditionSelectWidget();

    // set defect_types_modle
    void setupDefectTypesModel(const QStringList& list);

private:
    ConditionSelectWidgetPrivate* data_;

	/// <summary>
	/// 根据目前所有的条件框(ConditionWidgets)的条件设置情况生成query语句, 用于在数据库中取出满足所有条件的图片名字.
	/// </summary>
	/// <returns></returns>
    QString generateSqlQuery() const;

	/// <summary>
	/// 绑定所有spinbox(互相关联的)之间大小逻辑关系.即:最大值框的最小值比最小值框的目前的值更大, 最小值框情况类似.
	/// </summary>
	/// <param name="widget">当前正在被设置的ConditionWidget的指针.</param>
	void initSpinBoxBignessLogic(ConditionWidget const* widget);

	/// <summary>
	/// 设置条件框中至少有一个groupbox是被设置成有效的.
	/// </summary>
	/// <param name="widget">当前正在被设置的ConditionWidget的指针.</param>
	void initGroupBoxLogic(ConditionWidget const* widget);
};

#endif // CONDITIONSELECTWIDGET_H
