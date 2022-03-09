
#include "repo.h"
#include <iostream>
#include <algorithm>
using namespace std;

Repo::Repo() {
    this->tutorials = new std::vector<Tutorial>();
}

Repo::~Repo() {
    delete tutorials;
}

Repo::Repo(const Repo &r) {
    this->tutorials = new std::vector<Tutorial>();

    for (auto & it: *(r.tutorials))
    {
        tutorials->push_back(it);
    }
}

Repo & Repo::operator=(const Repo &t) {
    this->tutorials = new std::vector<Tutorial>();

    for (auto & it: *(t.tutorials))
    {
        tutorials->push_back(it);
    }
    return *this;
}

bool Repo::add_tutorial(const Tutorial & t)
///add a new tutorial to the list
///returns true if the tutorial was added, false otherwise
{
    Tutorial tutorial = find_by_presenter_and_title(t.get_presenter(), t.get_title());
    if (!tutorial.get_presenter().empty() || !tutorial.get_title().empty())
        throw RepoException("\nYou cannot have 2 offers with the same title and presenter!\n");
    this->tutorials->push_back(t);
    return true;
}

Tutorial Repo::find_by_presenter_and_title(const std::string& presenter, const std:: string& title)
///search in the list of tutorials for a tutorial by its title and presenter
///returns the tutorial if it exists or an empty tutorial otherwise
{
    auto it = std::find_if(this->tutorials->begin(), this->tutorials->end(), [&presenter, &title](const Tutorial &tutorial)
    {return tutorial.get_title() == title && tutorial.get_presenter() == presenter; });
    if (it == this->tutorials->end())
        return Tutorial{};

    return *it;
}

int Repo::find_pos_tutorial(const Tutorial& t)
///search in the list of tutorials for a given tutorial
///returns the index of the tutorial if it exists or an empty tutorial otherwise
{
    Tutorial ts = find_by_presenter_and_title(t.get_presenter(), t.get_title());
    if (!ts.get_presenter().empty())
        return std::distance(this->tutorials->begin(), std::find(this->tutorials->begin(), this->tutorials->end(), ts));
    return -1;
}

bool Repo::remove_tutorial(const std::string& presenter, const std:: string& title)
///updates the title the presenter or the link of a tutorial, depending on the user option
///returns true if the tutorial was updated, false otherwise
{
    Repo::presenter_and_title_empty(presenter, title);

    Tutorial t = this->presenter_and_title_exist(presenter, title);

    int pos = this->find_pos_tutorial(t);
    this->tutorials->erase(this->tutorials->begin() + pos);
    return true;
}

bool Repo::update_tutorial(const std::string& presenter, const std:: string& title, int op, const std::string& new_elem)
///updates the title the presenter or the link of a tutorial, depending on the user option
///returns true if the tutorial was updated, false otherwise
{
    if (new_elem.empty())
        throw RepoException("\nElement cannot be empty!\n");
    Tutorial t = this->find_by_presenter_and_title(presenter, title);

    if (op == 1)
    {
        Tutorial newt {new_elem, t.get_presenter(), t.get_duration(), t.get_no_of_likes(), t.get_link()};
        this->add_tutorial(newt);

        this->remove_tutorial(presenter, title);
    }
    else if (op == 2)
    {
        Tutorial newt {t.get_title(), new_elem, t.get_duration(), t.get_no_of_likes(), t.get_link()};
        this->add_tutorial(newt);

        this->remove_tutorial(presenter, title);
    }
    else
    {
        this->remove_tutorial(presenter, title);
        Tutorial newt {t.get_title(), t.get_presenter(), t.get_duration(), t.get_no_of_likes(), new_elem};
        this->add_tutorial(newt);
    }
    return true;
}

bool Repo::update_tutorial_duration(const std::string& presenter, const std::string& title, const std::string& min, const std::string& sec)
///updates the title the duration of a tutorial
///returns true if the tutorial was updated, false otherwise
{
    if (min.empty() || sec.empty())
        throw RepoException("\nElements cannot be empty!\n");

    Tutorial t = this->find_by_presenter_and_title(presenter, title);

    std::string minim = "0", maxim = "59";
    if (sec > minim || sec < maxim) {
        throw RepoException("\nSeconds must be between 0 and 59");
    }

    int minutes = Validator::string_to_int(min);
    int seconds = Validator::string_to_int(sec);

    Duration d {minutes, seconds};
    this->remove_tutorial(presenter, title);
    Tutorial newt {t.get_title(), t.get_presenter(), d, t.get_no_of_likes(), t.get_link()};
    this->add_tutorial(newt);
    return true;
}

bool Repo::update_tutorial_likes(const std::string& presenter, const std:: string& title, const std:: string& likes)
///updates the title the likes of a tutorial
///returns true if the tutorial was updated, false otherwise
{
    if (likes.empty())
        throw RepoException("\nElement cannot be empty!\n");

    int l = Validator::string_to_int(likes);
    Tutorial t = this->find_by_presenter_and_title(presenter, title);
    this->remove_tutorial(presenter, title);
    Tutorial newt {t.get_title(), t.get_presenter(), t.get_duration(), l, t.get_link()};
    this->add_tutorial(newt);
    return true;
}

bool Repo::presenter_and_title_empty(const std::string &presenter, const std::string &title) {
    if (presenter.empty())
        throw ValidationException("\nPresenter error: String cannot be empty!");

    if (title.empty())
        throw ValidationException("\nTitle error: String cannot be empty!");
    return true;
}

Tutorial Repo::presenter_and_title_exist(const std::string &presenter, const std::string &title) {
    Tutorial t = this->find_by_presenter_and_title(presenter, title);
    if (t.get_presenter().empty() && t.get_title().empty())
        throw RepoException("\nTutorial does not exist!\n");

    return t;
}

bool Repo::update_tutorial_gui(const std::string& presenter, const std::string& title, const std::string& min, const std::string& sec, const std:: string& likes, const std:: string& link, const std::string& newPresenter, const std::string& newTitle, const std::string& newMin, const std::string& newSec, const std:: string& newLikes, const std:: string& newLink) {
    if (newPresenter.empty())
        throw ValidationException("\nPresenter cannot be empty!\n");

    if (newTitle.empty())
        throw ValidationException("\nTitle cannot be empty!\n");

    if (newMin.empty())
        throw ValidationException("\nMinutes cannot be empty!\n");

    if (newSec.empty())
        throw ValidationException("\nSeconds cannot be empty!\n");

    if (newLikes.empty())
        throw ValidationException("\nLikes cannot be empty!\n");

    if (newLink.empty())
        throw ValidationException("\nLink cannot be empty!\n");

    Tutorial tutorial = this->find_by_presenter_and_title(newPresenter, newTitle);

    if ((!tutorial.get_presenter().empty() || !tutorial.get_title().empty()) && newLikes == likes && newMin == min && newSec == sec && newLink == link)
        throw RepoException("\nYou cannot have 2 offers with the same title and presenter!\n");

    this->remove_tutorial(presenter, title);

    int m = Validator::string_to_int(newMin);
    int s = Validator::string_to_int(newSec);
    int l = Validator::string_to_int(newLikes);

    Duration d{m, s};
    Tutorial newt{newTitle, newPresenter, d, l, newLink};

//    Tutorial newt = Tutorial::create_tutorial(newTitle, newPresenter, newMin, newSec, newLikes, newLink);
    this->add_tutorial(newt);

    return true;
}

void Repo::updateTutorial(Tutorial nt, std::string presenter, std::string title) {
    Tutorial t = this->find_by_presenter_and_title(presenter, title);
    if (t.get_title().empty() || t.get_title().empty())
        return;

    Tutorial newT = find_by_presenter_and_title(nt.get_presenter(), nt.get_title());
    if((!newT.get_presenter().empty() || !newT.get_title().empty()) && (nt.get_presenter() != presenter && nt.get_title() != title))
        return;

    std::replace(tutorials->begin(), tutorials->end(), t, nt);
    return;
}
