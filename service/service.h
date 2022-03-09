#pragma once

#include <repo.h>
#include "../repo/repo.h"
#include "../repo/FileRepo.h"
#include "../repo/HTMLRepo.h"
#include "../repo/CSVRepo.h"
#include "../iterator/iterator.h"
#include "../undo&redo/Action.h"

class Service
{
private:
    IFileRepo* repo;
    IFileRepo* watchlist;
    Iterator iter;
    std::vector<Action*> undoStack;
    std::vector<Action*> redoStack;
    int canRedo = 0;

public:
    Service(IFileRepo* r, IFileRepo* w) : iter() {
        repo = r;
        watchlist = w;
    };

    Service(const Service &c, Repo *Repo);
    ~Service();
    Service& operator= (const Service& c);

    //administrator mode functionalities
    IFileRepo* get_repo() const { return repo; }

    bool add_tutorial_service(const std::string& title, const std::string& presenter, const std::string& min, const std::string& sec, const std::string& likes, const std::string& link);

    bool remove_tutorial_service(const std::string& presenter, const std:: string& title);

    bool update_tutorial_service(const std::string& presenter, const std:: string& title, int op, const std::string& new_elem);

    bool update_tutorial_duration_service(const std::string& presenter, const std:: string& title, const std::string& min, const std::string& sec);

    bool update_tutorial_likes_service(const std::string& presenter, const std:: string& title, const std:: string& likes);

    bool update_tutorial_gui_service(const std::string& presenter, const std::string& title, const std::string& min, const std::string& sec, const std:: string& likes, const std:: string& link, const std::string& newPresenter, const std::string& newTitle, const std::string& newMin, const std::string& newSec, const std:: string& newLikes, const std:: string& newLink);

    void undo();

    void redo();

    //user mode functionalities
    IFileRepo *get_wathlist() const {return watchlist; }

    void create_iterator(const std::string &presenter);

    void start_iteration();

    Tutorial get_current_tutorial();

    void next();

    bool add_tutorial_watchlist(const Tutorial & t);

    bool delete_tutorial_watchlist(const std::string& presenter, const std:: string& title);

    Tutorial find_by_presenter_and_title_watchlist(const std::string& presenter, const std:: string& title);

    int like_tutorial(const std::string& presenter, const std:: string& title);

    Iterator get_iterator() {return iter; }
};
