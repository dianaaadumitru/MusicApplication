
#include "service.h"
#include <iostream>
#include "../undo&redo/ActionAdd.h"
#include "../undo&redo/ActionRemove.h"
#include "../undo&redo/ActionUpdate.h"

using namespace std;

Service::Service(const Service &c, Repo *Repo)
{
    repo = c.repo;
    iter = c.iter;
    watchlist = c.watchlist;
}

Service::~Service()
{
    delete repo;
    delete watchlist;
}

Service & Service::operator=(const Service & c)
{
    repo = c.get_repo();
    //repo = c.getRepo();
    iter = c.iter;
    watchlist = c.watchlist;
    return *this;
}

bool Service::add_tutorial_service(const std::string& title, const std::string& presenter, const std::string& min, const std::string& sec, const std::string& likes, const std::string& link)
///add a new tutorial to the list
///returns true if the tutorial was added, false otherwise
{
    std::string minim = "0", maxim = "59";
    if (sec < minim || sec > maxim){
        throw ValidationException("\nSeconds must be between 0 and 59");
    }

    if (title.empty())
        throw ValidationException("\nInvalid data");

    if (presenter.empty())
        throw ValidationException("\nInvalid data");

    if (min.empty())
        throw ValidationException("\nInvalid data");

    if (sec.empty())
        throw ValidationException("\nInvalid data");

    if (likes.empty())
        throw ValidationException("\nInvalid data");

    if (link.empty())
        throw ValidationException("\nInvalid data");

    int m = Validator::string_to_int(min);
    int s = Validator::string_to_int(sec);
    int l = Validator::string_to_int(likes);
    Tutorial t{title, presenter, Duration{m, s}, l, link};
    bool ok = this->repo->add_tutorial(t);
    if (ok){
        Action* addAction = new ActionAdd{this->repo, t};
        undoStack.push_back(addAction);
    }
    if (!canRedo)
        this->redoStack.clear();
    return ok;
}

bool Service::remove_tutorial_service(const std::string& presenter, const std:: string& title)
///search in the list of tutorials for a tutorial by its title and presenter
///returns the tutorial if it exists or an empty tutorial otherwise
{
    Tutorial t = this->repo->find_by_presenter_and_title(presenter, title);
    bool ok = this->repo->remove_tutorial(presenter, title);
    if (ok){
        Action* removeAction = new ActionRemove{this->repo, t};
        undoStack.push_back(removeAction);
    }
    if (!canRedo)
        this->redoStack.clear();
    return ok;
}

bool Service::update_tutorial_service(const std::string& presenter, const std:: string& title, int op, const std::string& new_elem)
///updates the title the presenter or the link of a tutorial, depending on the user option
///returns true if the tutorial was updated, false otherwise
{
    return this->repo->update_tutorial(presenter, title, op, new_elem);
}

bool Service::update_tutorial_duration_service(const std::string& presenter, const std::string& title, const std::string& min, const std::string& sec)
///updates the title the duration of a tutorial
///returns true if the tutorial was updated, false otherwise
{
    return this->repo->update_tutorial_duration(presenter, title, min, sec);
}

bool Service::update_tutorial_likes_service(const std::string& presenter, const std:: string& title, const std:: string& likes)
///updates the title the likes of a tutorial
///returns true if the tutorial was updated, false otherwise
{
    return this->repo->update_tutorial_likes(presenter, title, likes);
}

void Service::create_iterator(const std::string & presenter)
///creates an iterator
///returns a dynamic array that contains the whole list or the tutorials from a given presenter
{
    this->iter.iterator_empty();
    std::vector<Tutorial>* t = this->repo->get_tutorials();
    if (presenter.empty())
    {
        for (auto & it: *t) {
            this->iter.add(it);
        }
    } else {
        for (auto&  it: *t){
            if (it.get_presenter() == presenter)
                this->iter.add(it);
        }
    }
}

void Service::start_iteration()
///play the first tutorial from iteration
{
    this->iter.open();
}

Tutorial Service::get_current_tutorial()
///returns the current tutorial from the iterator
{
    return this->iter.get_current_tutorial();
}

void Service::next()
///plays the next tutorial from the iterator
{
    this->iter.next();
}

bool Service::add_tutorial_watchlist(const Tutorial & t)
///add a new tutorial to the watchlist
///returns true if the tutorial was added, false otherwise
{
    return this->watchlist->add_tutorial(t);
}

bool Service::delete_tutorial_watchlist(const std::string &presenter, const std::string &title)
///deletes a tutorial from the watchlist
{
    return this->watchlist->remove_tutorial(presenter, title);
}

Tutorial Service::find_by_presenter_and_title_watchlist(const std::string& presenter, const std:: string& title)
///search in the list of tutorials for a tutorial by its title and presenter
///returns the tutorial if it exists or an empty tutorial otherwise

{
    return this->watchlist->find_by_presenter_and_title(presenter, title);
}

int Service::like_tutorial(const std::string &presenter, const std::string &title)
///likes a tutorial from the watchlist
{
    Tutorial t = this->find_by_presenter_and_title_watchlist(presenter, title);
    t.like();
    int pos = this->repo->find_pos_tutorial(t);
    this->iter.update_likes(pos);
    return t.get_no_of_likes();
}

bool Service::update_tutorial_gui_service(const std::string& presenter, const std::string& title, const std::string& min, const std::string& sec, const std:: string& likes, const std:: string& link, const std::string& newPresenter, const std::string& newTitle, const std::string& newMin, const std::string& newSec, const std:: string& newLikes, const std:: string& newLink){
    bool ok =  this->repo->update_tutorial_gui(presenter, title, min, sec, likes, link, newPresenter, newTitle, newMin, newSec, newLikes, newLink);
    int m = Validator::string_to_int(min);
    int s = Validator::string_to_int(sec);
    int l = Validator::string_to_int(likes);
    Tutorial t{title, presenter, Duration{m, s}, l, link};

    int m2 = Validator::string_to_int(newMin);
    int s2 = Validator::string_to_int(newSec);
    int l2 = Validator::string_to_int(newLikes);
    Tutorial t2{newTitle, newPresenter, Duration{m2, s2}, l2, newLink};
    if (ok){
        Action* updateAction = new ActionUpdate{this->repo, t, t2};
        this->undoStack.push_back(updateAction);
    }
    if (!canRedo)
        this->redoStack.clear();
    return ok;
}

void Service::undo() {
    for (int i = 0; i < undoStack.size(); ++i) {
    }
    if (this->undoStack.empty())
        throw RepoException("You cannot undo anymore!");
    this->canRedo = 1;
    this->undoStack[this->undoStack.size() - 1]->executeUndo();
    redoStack.push_back(undoStack[this->undoStack.size() - 1]);
    this->undoStack.pop_back();
    this->canRedo = 0;
}

void Service::redo() {
    if (this->redoStack.empty())
        throw RepoException("You cannot redo anymore!");
    this->canRedo = 1;
    this->redoStack[this->redoStack.size() - 1]->executeRedo();
    undoStack.push_back(this->redoStack[this->redoStack.size() - 1]);
    this->redoStack.pop_back();
    this->canRedo = 0;
}
