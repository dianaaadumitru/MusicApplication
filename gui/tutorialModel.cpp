
#include "tutorialModel.h"

tutorialModel::tutorialModel(IFileRepo *repo) {
    this->repo = repo;
}

int tutorialModel::rowCount(const QModelIndex &parent) const {
    return this->repo->get_tutorials()->size();
}

int tutorialModel::columnCount(const QModelIndex &parent) const {
    return 5;
}

QVariant tutorialModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();
    //if (index.column() == 1) {
    auto v = repo->get_tutorials();

    auto tut = (*v)[index.row()];
    //}
    switch (index.column()) {
        case 0: {
            return tr(tut.get_presenter().c_str());
        }
        case 1:
            return tr(tut.get_title().c_str());
        case 2: {
            std::string duration = std::to_string(tut.get_duration().getMinutes()) + ":" + std::to_string(tut.get_duration().getSeconds());
            return tr(duration.c_str());
        }
        case 3:
            return tr(std::to_string(tut.get_no_of_likes()).c_str());
        case 4:
            return tr(tut.get_link().c_str());
        default:
            return QVariant();
    }
    return QVariant();
}

QVariant tutorialModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return tr("Presenter");

            case 1:
                return tr("Title");
            case 2:
                return tr("Duration");
            case 3:
                return tr("No. likes");
            case 4:
                return tr("Link");
            default:
                return QVariant();
        }
    }
    return QVariant();
}

bool tutorialModel::addTutorialToRepository(Tutorial t) {
    try {

        beginInsertRows(QModelIndex(), 0, 0);
        repo->add_tutorial(t);
        endInsertRows();
        return true;
    }
    catch (RepoException &e)
    {
        throw e;
    }
    catch (ValidationException &e) {
        throw e;
    }
}

bool tutorialModel::removeTutorialFromRepository(int row) {
    Tutorial v = (*repo->get_tutorials())[row];
    beginInsertRows(QModelIndex(), 0, 0);
    repo->remove_tutorial(v.get_presenter(), v.get_title());
//    endInsertRows();
//    endRemoveRows();
    return true;
}

bool tutorialModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (role != Qt::EditRole)
        return false;

    int row = index.row();
    int  col = index.column();

    Tutorial t= (*repo->get_tutorials())[row];

    switch (col) {
        case 0: {
            std::string presenter{value.toString().toStdString()};
            t.set_presenter(presenter);
            break;
//            repo->updateTutorial(CreateTutorial::create_tutorial(t.get_title(), t.get_presenter(), std::to_string(t.get_duration().getMinutes()), std::to_string(t.get_duration().getSeconds()), std::to_string(t.get_no_of_likes()), t.get_link()), presenter, t.get_title());
//            Tutorial newt = Tutorial{t.get_title(), t.get_presenter(), Duration{t.get_duration().getMinutes(), t.get_duration().getSeconds()}, t.get_no_of_likes(), t.get_link()};
        }
        default:
            break;
    }

    return false;
}

Qt::ItemFlags tutorialModel::flags(const QModelIndex &index) const {
    return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}


