#pragma once

//#include "../dynamic_vector/array.h"
#include "../domain/domain.h"
#include <vector>


class Repo
{
private:
   std::vector<Tutorial>* tutorials;

public:
    /*
     Constructor, initializes an object of type repo
     */
    Repo();
    ~Repo();
    Repo(const Repo& r);
    Repo& operator=(const Repo& t);

    bool add_tutorial(const Tutorial & t);

    Tutorial find_by_presenter_and_title(const std::string& presenter, const std:: string& title);

    std::vector<Tutorial>* get_tutorials() {return tutorials; }

    bool remove_tutorial(const std::string& presenter, const std:: string& title);

    int find_pos_tutorial(const Tutorial& t);

    bool update_tutorial(const std::string& presenter, const std::string& title, int op, const std::string& new_elem);

    bool update_tutorial_duration(const std::string& presenter, const std::string& title, const std::string& min, const std::string& sec);

    bool update_tutorial_likes(const std::string& presenter, const std:: string& title, const std:: string& likes);

    static bool presenter_and_title_empty(const std::string& presenter, const std:: string& title);

    Tutorial presenter_and_title_exist(const std::string& presenter, const std:: string& title);

    bool update_tutorial_gui(const std::string& presenter, const std::string& title, const std::string& min, const std::string& sec, const std:: string& likes, const std:: string& link, const std::string& newPresenter, const std::string& newTitle, const std::string& newMin, const std::string& newSec, const std:: string& newLikes, const std:: string& newLink);

    void updateTutorial(Tutorial nt, std::string presenter, std::string title);
};

class RepoException : public ValidationException {
public:
    RepoException(std::string message): ValidationException(message){}
};
