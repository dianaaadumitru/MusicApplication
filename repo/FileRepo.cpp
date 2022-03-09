
#include "FileRepo.h"
#include <fstream>


void FileRepo::repoFromFile()
{
    std::ifstream infile(source);
    if (!infile.is_open())
        throw RepoException("Cannot open file: " + source);
    Tutorial t;
    while (infile >> t)
    {
        this->add_tutorial(t);
    }
    infile.close();
}

void FileRepo::repoToFile()
{
    std::ofstream outFile(source);
    std::vector<Tutorial>* s = this->get_tutorials();
    for (auto&it : *s)
        outFile << it << std::endl;
    outFile.close();
}

FileRepo::FileRepo(const std::string & source) : IFileRepo(source) {
    this->repoFromFile();
}

FileRepo::~FileRepo()
{
//    this->repoToFile();
}

void FileRepo::display()
{
    std::string s = "notepad \"" + this->source + "\"";
    system(s.c_str());
}
