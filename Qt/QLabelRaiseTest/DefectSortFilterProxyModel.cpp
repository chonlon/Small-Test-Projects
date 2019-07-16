#include "DefectSortFilterProxyModel.h"



DefectSortFilterProxyModel::DefectSortFilterProxyModel()
{
}


DefectSortFilterProxyModel::~DefectSortFilterProxyModel()
{
}

bool DefectSortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex & sourceParent) const
{
	auto index = sourceModel()->index(sourceRow, 1, sourceParent);
	return index.data().toDouble() >= filter_min && index.data().toDouble() <= filter_max;
}

bool DefectSortFilterProxyModel::lessThan(const QModelIndex & left, const QModelIndex & right) const
{
	return left.data().toDouble() > right.data().toDouble();
}
