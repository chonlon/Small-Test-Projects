#ifndef _DEFECTSORTFILTERPROXYMODEL_H__
#define _DEFECTSORTFILTERPROXYMODEL_H__
#include <QSortFilterProxyModel>

class DefectSortFilterProxyModel :
	public QSortFilterProxyModel
{
	Q_OBJECT
public:
	DefectSortFilterProxyModel();
	~DefectSortFilterProxyModel();

	inline void setFilter(double _filter_min, double _filter_max) {
		filter_min = _filter_min;
		filter_max = _filter_max;
		invalidateFilter();
	}
protected:
	// 筛选符合条件的行, 内部会调用.
	// sourceRow为当前判断行, parent为父对象.
	bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
	bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;

private:
	double filter_min;
	double filter_max;
};

#endif //!_DEFECTSORTFILTERPROXYMODEL_H__
