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

    QString generateSqlQuery();

	void initSpinBoxBignessLogic(ConditionWidget const* widget);
};

#endif // CONDITIONSELECTWIDGET_H
