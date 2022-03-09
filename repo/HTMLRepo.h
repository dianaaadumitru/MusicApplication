#pragma once
#include "IFileRepo.h"

class HTMLRepo : public IFileRepo{
protected:
    void repoFromFile() override;
    void repoToFile() override;

public:
    std::string site;
//    HTMLRepo(const std::string& source, const std::string& site);
    HTMLRepo(const std::string& source): IFileRepo(source){this->repoFromFile(); };
    ~HTMLRepo() ;
    void display() override;
};



