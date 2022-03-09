#pragma once
#include <QAbstractTableModel>
#include <functional>
#include <vector>
#include "IFileRepo.h"
#include <memory>

class tutorialModel : public QAbstractTableModel{
private:
    IFileRepo *repo;
//    std::vector<std::unique_ptr<Action>> undoAction;

public:
    tutorialModel(IFileRepo * repo);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    IFileRepo* getRepo() { return repo; };
    bool addTutorialToRepository(Tutorial t);
    bool removeTutorialFromRepository(int row);
    bool setData(const QModelIndex& index, const QVariant& value, int role) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
};

