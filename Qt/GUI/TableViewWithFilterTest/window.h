#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QTableView>
#include <QLineEdit>
#include <QPushButton>
#include "defectsortfilterproxymodel.h"
#include "FilterWidget.h"

class Window : public QWidget
{
    Q_OBJECT

public:
    Window(QWidget *parent = nullptr);
    ~Window();

    Q_INVOKABLE void doFilter();

    void setSourceModel(QAbstractItemModel *model);
private:
    QLineEdit *m_filter_edit;
    QPushButton *m_filter_button;

    QTableView *m_p_orgin_table_view;
    QTableView *m_p_filtered_table_view;

    FilterWidget *filter_widget;

    DefectSortFilterProxyModel *m_filter_model;
};

#endif // WINDOW_H
