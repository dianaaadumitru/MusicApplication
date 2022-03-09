//
// Created by diana on 5/16/2021.
//

#include "NumericFilterProxyModel.h"

NumericFilterProxyModel::NumericFilterProxyModel(QObject *parent) : QSortFilterProxyModel(parent) {

}

bool NumericFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const {
    QModelIndex index0 = sourceModel()->index(sourceRow, 0, sourceParent);
    QModelIndex index1 = sourceModel()->index(sourceRow, 1, sourceParent);
    QModelIndex index2 = sourceModel()->index(sourceRow, 2, sourceParent);
    QModelIndex index3 = sourceModel()->index(sourceRow, 3, sourceParent);
    QModelIndex index4 = sourceModel()->index(sourceRow, 4, sourceParent);
    QString s = index0.data().toString() + index1.data().toString() + index2.data().toString() + index3.data().toString() + index4.data().toString();

    return s.contains(filterValue);
}

bool NumericFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const {
    return false;
}
