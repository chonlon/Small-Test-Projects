#ifndef DEFECTSORTFILTERPROXYMODEL_H
#define DEFECTSORTFILTERPROXYMODEL_H

#include <QObject>
#include <QSortFilterProxyModel>

class DefectSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    DefectSortFilterProxyModel(QObject *parent = nullptr);

    inline void setFilter(int num) {
        m_filter = num;
        invalidateFilter();
    }

protected:
    // 筛选符合条件的行, 内部会调用.
    // sourceRow为当前判断行, parent为父对象.
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;

private:
    int m_filter;
};

#endif // DEFECTSORTFILTERPROXYMODEL_H
