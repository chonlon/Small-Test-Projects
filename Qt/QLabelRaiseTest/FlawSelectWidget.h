#pragma once

#include <QWidget>

class FlawSelectWidgetPrivate;

class FlawSelectWidget :
    public QWidget
{
    Q_OBJECT
public:
    FlawSelectWidget(QWidget *parent = nullptr);
    ~FlawSelectWidget();

private:
	Q_INVOKABLE void onButtonClicked();

	/// <summary>
	/// 初始化界面上部按钮组.
	/// </summary>
	void initButtonGroup();

	void initLayout();
	void initConnect();

	FlawSelectWidgetPrivate* m_data;
};

//#endif // !_FlawSelectWidget_H__
