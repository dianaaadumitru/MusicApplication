#include <QMessageBox>
#include "gui2.h"
#include "ui_gui2.h"
#include "PlayButtonDelegate.h"
#include <sstream>
#include <QPushButton>

gui2::~gui2() {
    delete ui;
}

gui2::gui2(Service *s, QWidget *parent) :
        QWidget(parent), ui(new Ui::gui2), s(s) {
    ui->setupUi(this);

    model = new tutorialModel{ s->get_repo() };
    watchlistModel = new tutorialModel{ s->get_wathlist() };

    viewsFilter = new NumericFilterProxyModel{};
    viewsFilter->setSourceModel(model);

    ui->watchlistView->setModel(watchlistModel);
////    ui->watchlistView->resizeColumnsToContents();
    ui->watchlistView->resizeColumnToContents(5);
    ui->watchlistView->resizeRowsToContents();

    ui->watchlistView->setItemDelegate(new PlayButtonDelegate{});
    ui->watchlistView->setColumnWidth(6, 650);

    populateList();
    connectSignalAndSlots();
    selectTutorial();
}

void gui2::connectSignalAndSlots() {
    QObject::connect(ui->addButton, &QPushButton::clicked, this, &gui2::addTutorial);
    QObject::connect(ui->removeButton, &QPushButton::clicked, this, &gui2::removeTutorial);
    QObject::connect(ui->removeWatchlistButton, &QPushButton::clicked, this, &gui2::removeFromWatchlist);
    QObject::connect(ui->searchButton, &QPushButton::clicked, this, &gui2::configureIterator);
    QObject::connect(ui->nextButton, &QPushButton::clicked, this, &gui2::next);
    QObject::connect(ui->viewWatchlistButton, &QPushButton::clicked, this, &gui2::viewWatchlist);
    QObject::connect(ui->addButton_4, &QPushButton::clicked, this, &gui2::addToWatchlist);
    QObject::connect(ui->updateButton, &QPushButton::clicked, this, &gui2::updateTutorialAdmin);
    QObject::connect(ui->tutorialView, &QTableView::clicked, this, &gui2::selectTutorial);
    QObject::connect(ui->undoButton, &QPushButton::clicked, this, &gui2::undo);
    QObject::connect(ui->redoButton, &QPushButton::clicked, this, &gui2::redo);
}

void gui2::addTutorial() {
    std::string presenter = ui->presenterLineEdit->text().toStdString();
    std::string title = ui->titleLineEdit_2->text().toStdString();
    std::string min = ui->minLineEdit->text().toStdString();
    std::string sec = ui->secLineEdit->text().toStdString();
    std::string likes = ui->likesLineEdit->text().toStdString();
    std::string link = ui->linkLineEdit->text().toStdString();

    try {
        this->s->add_tutorial_service(title, presenter, min, sec, likes, link);
    } catch (RepoException& e){
        QMessageBox messageBox;
        messageBox.critical(0, "Error", "Cannot add element! Tutorial already exists");
    }
    catch (ValidationException& e){
        QMessageBox messageBox;
        messageBox.critical(0, "Error", QString::fromStdString("Invalid data!"));
    }

    this->populateList();

    int lastElement = this->s->get_repo()->get_tutorials()->size() - 1;
    ui->tutorialView->setCurrentRow(lastElement);

}

void gui2::removeTutorial() {
    std::string presenter = ui->presenterLineEdit->text().toStdString();
    std::string title = ui->titleLineEdit_2->text().toStdString();
    try {
        this->s->remove_tutorial_service(presenter, title);
    } catch (RepoException& e){
        QMessageBox messageBox;
        messageBox.critical(0, "Error", "This tutorial doesn't exist!");
    }
    catch (ValidationException& e){
        QMessageBox messageBox;
        messageBox.critical(0, "Error", QString::fromStdString("Invalid data!"));
    }
    this->populateList();
}

void gui2::configureIterator() {
    iterator.iterator_empty();
    std::string presenter = ui->presenterFilter->text().toStdString();
    std::vector<Tutorial>* s = model->getRepo()->get_tutorials();
    if (presenter.empty()) {
        for (auto& it : *s) {
            iterator.add(it);
        }
    }
    else {
        for (auto& it : *s) {
            if (it.get_presenter() == presenter)
                iterator.add(it);
        }
    }
    iterator.open();
    updateTutorial();
}

void gui2::updateTutorial() {
    Tutorial t = iterator.get_current_tutorial();
    ui->presenterLabel->setText(QString(t.get_presenter().c_str()));
    ui->titlelabel->setText(QString(t.get_title().c_str()));
    ui->linkLabel->setText(QString(t.get_link().c_str()));
    ui->noLikesLabel_2->setText(QString(std::to_string(t.get_no_of_likes()).c_str()));
    std::string duration = std::to_string(t.get_duration().getMinutes()) + ":" + std::to_string(t.get_duration().getSeconds());
    ui->durationLabel->setText(QString(duration.c_str()));

}

void gui2::removeFromWatchlist() {
    QItemSelectionModel *select = ui->watchlistView->selectionModel();
    QModelIndexList s = select->selectedRows();
    if (s.isEmpty()) {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", QString::fromStdString("You didn't select any tutorial!"));
        return;
    }
    auto index = s.at(0);
    if (index.isValid()) {
        QString cellText = index.data().toString();
        int row = index.row();


        QMessageBox msgBox{};
        msgBox.setWindowTitle("like");
        msgBox.setText("Do you want to like this video?");
        QPushButton *yes = msgBox.addButton("yes", QMessageBox::AcceptRole);
        QPushButton *no = msgBox.addButton("no", QMessageBox::ActionRole);
        QObject::connect(yes, &QPushButton::clicked, [this]() {
            Tutorial t = getSelectedTutorial();
            int l = t.get_no_of_likes() + 1;
//            this->s->update_tutorial_gui_service(t.get_presenter(), t.get_title(),
//                                                 std::to_string(t.get_duration().getMinutes()),
//                                                 std::to_string(t.get_duration().getSeconds()),
//                                                 std::to_string(t.get_no_of_likes()), t.get_link(), t.get_presenter(),
//                                                 t.get_title(), std::to_string(t.get_duration().getMinutes()),
//                                                 std::to_string(t.get_duration().getSeconds()), std::to_string(l),
//                                                 t.get_link());
            this->s->update_tutorial_likes_service(t.get_presenter(), t.get_title(), std::to_string(l));
//            this->s->update_tutorial_likes_service(t.get_presenter(), t.get_title(), std::to_string(l));
            this->populateList();
        });
        msgBox.exec();
        auto v = watchlistModel->removeTutorialFromRepository(row);
    }
}

void gui2::next() {
    iterator.next();
    updateTutorial();
}

void gui2::viewWatchlist() {
    this->s->get_wathlist()->repoToFile();
    this->s->get_wathlist()->display();
}

void gui2::addToWatchlist() {
    Tutorial t = iterator.get_current_tutorial();
    try {
        watchlistModel->addTutorialToRepository(t);
    } catch (RepoException& e){
        QMessageBox messageBox;
        messageBox.critical(0, "Error", "Cannot add element! Tutorial already exists");
    }
    catch (ValidationException& e){
        QMessageBox messageBox;
        messageBox.critical(0, "Error", QString::fromStdString("Invalid data!"));
    }
}

int gui2::getSelectedIndex() {
    QModelIndexList selectedIndexes = ui->tutorialView->selectionModel()->selectedIndexes();
    if (selectedIndexes.size() == 0){
        ui->presenterLineEdit->clear();
        ui->titleLineEdit_2->clear();
        ui->minLineEdit->clear();
        ui->secLineEdit->clear();
        ui->likesLineEdit->clear();
        ui->linkLineEdit->clear();
        return -1;
    }
    int selectedIndex = selectedIndexes.at(0).row();
    return selectedIndex;
}

Tutorial gui2::getSelectedTutorial() {
    int selectedIndex = this->getSelectedIndexUser();
    if (selectedIndex < 0)
        return Tutorial();
    std::vector<Tutorial> *allTutorials = this->s->get_repo()->get_tutorials();
    Tutorial t;
    int i = 0;
    for (auto& it : *allTutorials)
    {
        if (i == selectedIndex){
            t = it;
            break;
        }
        i++;
    }
    return t;
}

void gui2::updateTutorialAdmin() {
    int selectedIndex = this->getSelectedIndex();

    if (selectedIndex < 0)
        return;
    std::vector<Tutorial> *allTutorials = this->s->get_repo()->get_tutorials();
    Tutorial t;
    int i = 0;
    for (auto& it : *allTutorials)
    {
        if (i == selectedIndex){
            t = it;
            break;
        }
        i++;
    }
    std::string presenter = ui->presenterLineEdit->text().toStdString();
    std::string title = ui->titleLineEdit_2->text().toStdString();
    std::string min = ui->minLineEdit->text().toStdString();
    std::string sec = ui->secLineEdit->text().toStdString();
    std::string likes = ui->likesLineEdit->text().toStdString();
    std::string link = ui->linkLineEdit->text().toStdString();

    try {
        this->s->update_tutorial_gui_service(t.get_presenter(), t.get_title(), std::to_string(t.get_duration().getMinutes()), std::to_string(t.get_duration().getSeconds()), std::to_string(t.get_no_of_likes()), t.get_link(), presenter, title, min, sec, likes, link);
    } catch (RepoException& e){
        QMessageBox messageBox;
        messageBox.critical(0, "Error", "Cannot update element! Tutorial already exists!");
    }
    catch (ValidationException& e){
        QMessageBox messageBox;
        messageBox.critical(0, "Error", QString::fromStdString("Invalid data!"));
    }

    this->populateList();

    int lastElement = this->s->get_repo()->get_tutorials()->size() - 1;
    ui->tutorialView->setCurrentRow(lastElement);
}

void gui2::selectTutorial() {
    int selectedIndex = this->getSelectedIndex();
    if (selectedIndex < 0)
        return;
    std::vector<Tutorial> *allTutorials = this->s->get_repo()->get_tutorials();
    Tutorial t;
    int i = 0;
    for (auto& it : *allTutorials)
    {
        if (i == selectedIndex){
            t = it;
            break;
        }
        i++;
    }
    ui->presenterLineEdit->setText(QString::fromStdString(t.get_presenter()));
    ui->titleLineEdit_2->setText(QString::fromStdString(t.get_title()));
    ui->minLineEdit->setText(QString::fromStdString(std::to_string(t.get_duration().getMinutes())));
    ui->secLineEdit->setText(QString::fromStdString(std::to_string(t.get_duration().getSeconds())));
    ui->likesLineEdit->setText(QString::fromStdString(std::to_string(t.get_no_of_likes())));
    ui->linkLineEdit->setText(QString::fromStdString(t.get_link()));

}

void gui2::populateList() {
    ui->tutorialView->clear();

    std::vector<Tutorial> *allTutorials = this->s->get_repo()->get_tutorials();
    for (Tutorial& t: *allTutorials){
        ui->tutorialView->addItem(QString::fromStdString(t.get_presenter() + ", " + t.get_title() + ", " + std::to_string(t.get_duration().getMinutes()) + ":" + std::to_string(t.get_duration().getSeconds()) + ", " + std::to_string(t.get_no_of_likes()) + ", " + t.get_link()));
    }
}

void gui2::undo() {
    try {
        this->s->undo();
        this->populateList();
    } catch (RepoException& e){
        QMessageBox messageBox;
        messageBox.critical(0, "Error", "You cannot undo anymore!");
    }
}

void gui2::redo() {
    try {
        this->s->redo();
        this->populateList();
    } catch (RepoException& e){
        QMessageBox messageBox;
        messageBox.critical(0, "Error", "You cannot redo anymore!");
    }
}

int gui2::getSelectedIndexUser() {
    return ui->watchlistView->selectionModel()->currentIndex().row();
}

