#pragma once
#include "repo.h"
// Our interface for creating repos that read and write to a specific type
class IFileRepo : public Repo {
protected:
    std::string source;
public:

    // pure abstract methods used for writing and reading a file
    virtual void repoFromFile() = 0;
    virtual void repoToFile() = 0;

    IFileRepo(const std::string& source) : Repo(), source(source) {}

    IFileRepo(const IFileRepo& fl) : Repo(fl), source(fl.source) {}

    virtual	~IFileRepo() = default;

    virtual void display() = 0;

};