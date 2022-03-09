
#include "HTMLRepo.h"
#include <Windows.h>
#include <fstream>
#include "../validator/validator.h"

using namespace std;

void HTMLRepo::repoFromFile()
{
//    std::ifstream file{this->source};
//
//    std::vector<Tutorial> turretsFromFile;
//    std::string buffer, title, presenter, minutes, auraLevel, numberOfSeparateParts;
//
//    for(int i=0; i<14; i++){
//        getline(file, buffer);
//    }
//
//    while(!file.eof()){
//        getline(file, buffer);
//        if(buffer == "</table>")
//            break;
//        getline(file, buffer);
//        auto indexToStop = buffer.find_last_of('<');
//        title = buffer.substr(4, indexToStop-4);
//
//        getline(file, buffer);
//        indexToStop = buffer.find_last_of('<');
//        presenter = buffer.substr(4, indexToStop-4);
//
//        getline(file, buffer);
//        indexToStop = buffer.find_last_of('<');
//        auraLevel = buffer.substr(4, indexToStop-4);
//
//        getline(file, buffer);
//        indexToStop = buffer.find_last_of('<');
//        numberOfSeparateParts = buffer.substr(4, indexToStop-4);
//
//        getline(file, buffer);
//        indexToStop = buffer.find_last_of('<');
//        minutes = buffer.substr(4, indexToStop-4);
//        cout<<minutes;
//
////        turretsFromFile.emplace_back(title, presenter, auraLevel, numberOfSeparateParts, vision);
//
//        getline(file, buffer);
//    }
//
//    file.close()
////    return turretsFromFile;
}


void HTMLRepo::repoToFile() {
    std::ofstream outFile(this->source);
//    outFile<<123;
    outFile << "<!DOCTYPE html>" << endl;
    outFile << "<html>" << endl;
    outFile << "<head><title>Watchlist</title></head>" << endl;
    outFile << R"(<body style="background-color:skyblue;"><table border="1">)" << endl;

    outFile << "<tr>" << endl;
    outFile << "<td>Title</td>" << endl;
    outFile << "<td>Presenter</td>" << endl;
    outFile << "<td>Duration</td>" << endl;
    outFile << "<td>Likes</td>" << endl;
    outFile << "<td>Link</td>" << endl;
    outFile << "</tr>" << endl;

    std::vector<Tutorial>* s = this->get_tutorials();
//    cout<<s->size();
    for (auto&it : *s){
//        cout<<123;
        outFile << "<tr>" << endl;
        outFile << "<td>" << it.get_title() << "</td>" << endl;
        outFile << "<td>" << it.get_presenter() << "</td>" << endl;
        outFile << "<td>" << it.get_duration().getMinutes()<<":"<<it.get_duration().getSeconds() << "</td>" << endl;
        outFile << "<td>" << it.get_no_of_likes() << "</td>" << endl;
        outFile << "<td>" << it.get_link() << "</td>" << endl;
        outFile << "</tr>" << endl;
    }
    outFile << "</table>" << endl;
    outFile << "</body>" << endl;
    outFile << "</html>" << endl;
    outFile.close();
}

//HTMLRepo::HTMLRepo(const std::string &source, const std::string& site): IFileRepo(source), site(site) {
//    std::cout << site;
//
//    this->repoFromFile();
//}

HTMLRepo::~HTMLRepo() {
    this->repoToFile();
}

void HTMLRepo::display() {
    std::string path = "\"" + this->source + "\"";
    ShellExecuteA(NULL, NULL, "chrome.exe", path.c_str(), NULL, SW_SHOWMAXIMIZED);
}