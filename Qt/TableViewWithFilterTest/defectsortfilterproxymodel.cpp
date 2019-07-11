#include "defectsortfilterproxymodel.h"

DefectSortFilterProxyModel::DefectSortFilterProxyModel(QObject *parent) : m_filters(3, 0)
{

}

bool DefectSortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    auto index_0 = sourceModel()->index(sourceRow, 0, sourceParent);
    auto index_1 = sourceModel()->index(sourceRow, 1, sourceParent);
    auto index_2 = sourceModel()->index(sourceRow, 2, sourceParent);

    return index_0.data().toInt() >= m_filters[0] && index_1.data().toInt() >= m_filters[1] && index_2.data().toInt() >= m_filters[2];
}

bool DefectSortFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    return left.data().toInt() < right.data().toInt();
}


