#include "CSVRepo.h"
#include <Windows.h>
#include <fstream>


void CSVRepo::repoFromFile()
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

void CSVRepo::repoToFile()
{
    std::ofstream outFile(source, std::ios::out);
    std::vector<Tutorial>* s = this->get_tutorials();
    for (auto&it : *s) {
//        std::cout<<"123";
        outFile << it << std::endl;
    }
    outFile.close();
}

CSVRepo::CSVRepo(const std::string & source) : IFileRepo(source) {
//    this->repoFromFile();
}

CSVRepo::~CSVRepo()
{
    this->repoToFile();
}

void CSVRepo::display()
{
    std::string path = "\"" + this->source + "\"";
    ShellExecuteA(NULL, NULL, "C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs\\Accessories\\Notepad", path.c_str(), NULL, SW_SHOWMAXIMIZED);
}
