//#pragma once
//
//#include "../domain/domain.h"
//#include <vector>
//#include <algorithm>
//#include "repo.h"
//
//class FileRepo {
//private:
//    std::vector<Tutorial>* tutorials;
//    std::string file_name;
//
//public:
//
//    //constructor + destructor
//    FileRepo(const std::string& file = "");
//    ~FileRepo() {};
//
//    std::vector<Tutorial> *load_from_file();
//    void store_to_file(std::vector<Tutorial> *tutorial_list);
//
//    std::vector<Tutorial>* get_tutorials() {std::vector<Tutorial> *tut = this->load_from_file(); return tut;};
//
//    bool add_tutorial(const Tutorial & t);
//
//    Tutorial find_by_presenter_and_title(const std::string& presenter, const std:: string& title);
//
//    int find_pos_tutorial(const Tutorial& t);
//
//    bool remove_tutorial(const std::string& presenter, const std:: string& title);
//
//    static bool presenter_and_title_empty(const std::string& presenter, const std:: string& title);
//
//    Tutorial presenter_and_title_exist(const std::string& presenter, const std:: string& title);
//
//    bool update_tutorial(const std::string& presenter, const std::string& title, int op, const std::string& new_elem);
//
//    bool update_tutorial_duration(const std::string& presenter, const std::string& title, const std::string& min, const std::string& sec);
//
//    bool update_tutorial_likes(const std::string& presenter, const std:: string& title, const std:: string& likes);
//
//};
//
//
#pragma once
#include "IFileRepo.h"

// Comma Separate Value - repository -> writes and reads to a text file in CSV format
class FileRepo : public IFileRepo {
protected:
    void repoFromFile() override;
    void repoToFile() override;

public:

    FileRepo(const std::string& source);
    ~FileRepo() ;
    void display() override;
};