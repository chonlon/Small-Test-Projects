#include "QFlawSortFilterProxyModel.h"


QFlawSortFilterProxyModel::QFlawSortFilterProxyModel()
{
}


QFlawSortFilterProxyModel::~QFlawSortFilterProxyModel()
{
}

bool QFlawSortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex & sourceParent) const
{
	auto index = sourceModel()->index(sourceRow, 1, sourceParent);
	return index.data().toDouble() >= filter_min && index.data().toDouble() <= filter_max;
}

bool QFlawSortFilterProxyModel::lessThan(const QModelIndex & left, const QModelIndex & right) const
{
	return left.data().toString() > right.data().toString();
}
