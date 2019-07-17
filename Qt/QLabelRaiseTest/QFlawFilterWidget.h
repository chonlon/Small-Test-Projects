#pragma once
#include <QWidget>
class QFlawFilterWidgetPrivate;
class QAbstractItemModel;
class QFlawFilterWidget :
	public QWidget
{
	Q_OBJECT
public:
	QFlawFilterWidget(QWidget *parent = nullptr);
	~QFlawFilterWidget();
private:
	Q_INVOKABLE void onButtonClicked();
	/// <summary>
	/// 初始化界面上部按钮组.
	/// </summary>
	void initButtonGroup();
	void initLayout();
	void initConnect();
	/// <summary>
	/// 通过GroupButton中被选中的Button对应的缺陷的名称获取响应的Model(数据), 用于显示.
	/// </summary>
	/// <param name="name">GroupButton中被选中的Button对应的缺陷的名称</param>
	QAbstractItemModel* getModelByName(const QString& name);
	QFlawFilterWidgetPrivate* m_data;
};
//#endif // !_FlawSelectWidget_H__