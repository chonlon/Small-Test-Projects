#include "defectsortfilterproxymodel.h"

DefectSortFilterProxyModel::DefectSortFilterProxyModel(QObject *parent) : m_filter{}
{

}

bool DefectSortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    auto index_0 = sourceModel()->index(sourceRow, 0, sourceParent);
    auto index_1 = sourceModel()->index(sourceRow, 1, sourceParent);
    auto index_2 = sourceModel()->index(sourceRow, 2, sourceParent);

    return index_0.data().toInt() >= m_filter && index_1.data().toInt() >= m_filter && index_2.data().toInt() >= m_filter;
}

bool DefectSortFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    return left.data().toInt() < right.data().toInt();
}


