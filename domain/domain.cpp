#include "domain.h"
#include <Windows.h>
#include <shellapi.h>
#include <string>
#include <vector>

#include <iostream>
using namespace std;

Tutorial::Tutorial() : title(""), presenter(""), duration(Duration()), likes(0), link("") {}

Tutorial::Tutorial(const std::string& title, const std::string& presenter, const Duration& duration, const int& likes, const std::string& link)
{
    this->title = title;
    this->presenter = presenter;
    this->duration = duration;
    this->likes = likes;
    this->link = link;
}

//Tutorial Tutorial::create_tutorial(const std::string &title, const std::string &presenter, const std::string &minutes,
//                                   const std::string &seconds, const std::string &likes, const std::string &link) {
//    std::string errors;
//    std::string valid_title;
//    std::string valid_presenter;
//    int min = 0, sec = 0, l = 0;
//    std::string valid_link;
//    try {
//        valid_title = Validator::is_string_empty(title);
//    } catch (ValidationException& e) {
//        errors += "\nTitle Error: " + std::string (e.which_message());
//    }
//
//    try {
//        valid_presenter = Validator::is_string_empty(presenter);
//    } catch (ValidationException& e) {
//        errors += "\nPresenter Error: " + std::string (e.which_message());
//    }
//
//    try {
//        min = Validator::string_to_int(minutes);
//    } catch (ValidationException& e) {
//        errors += "\nMinutes Error: " + std::string (e.which_message());
//    }
//
//    try {
//        sec = Validator::string_to_int(seconds);
//    } catch (ValidationException& e) {
//        errors += "\nSeconds Error: " + std::string (e.which_message());
//    }
//
//    try {
//        l = Validator::string_to_int(likes);
//    } catch (ValidationException& e) {
//        errors += "\nLikes Error: " + std::string (e.which_message());
//    }
//
//    try {
//        valid_link = Validator::is_string_empty(link);
//    } catch (ValidationException& e) {
//        errors += "\nLink Error: " + std::string (e.which_message());
//    }
//
//    if (!errors.empty())
//        throw ValidationException(errors);
//    return Tutorial(valid_title, valid_presenter, Duration(min, sec), l, valid_link);
//}

std::string Tutorial::get_title() const
{
    return this->title;
}

std::string Tutorial::get_presenter() const
{
    return this->presenter;
}

Duration Tutorial::get_duration() const
{
    return this->duration;
}

int Tutorial::get_no_of_likes() const
{
    return this->likes;
}

std::string Tutorial::get_link() const
{
    return this->link;
}

void Tutorial::open_link() const
{
    ShellExecuteA(NULL, NULL, "chrome.exe", this->get_link().c_str(), NULL, SW_SHOWMAXIMIZED);
}

void Tutorial::like()
{
    this->likes++;
}

bool Tutorial::operator==(const Tutorial & t)
{
    return this->get_presenter() == t.get_presenter() && this->get_title() == t.get_title();
}

std::ostream & operator << (std::ostream & out, const Tutorial & t)
{
    out << t.get_presenter().c_str() << "," << t.get_title().c_str() << "," << t.get_no_of_likes()  << "," << t.get_duration().getMinutes() << "," << t.get_duration().getSeconds() << "," << t.get_link().c_str();
    return out;
}

std::istream & operator >> (std::istream & in, Tutorial & t)
{
    std::string line;
    getline(in, line);
    if (line.empty())
        return in;

    std::vector<std::string> tokens = tokenize(line, ',');

    if (tokens.size() != 6) // make sure all the song data was valid
        throw ValidationException("Sorry! the number of fields is not ok!");
//    cout<<tokens[2]<<" "<<tokens[3]<<endl;
    t = CreateTutorial::create_tutorial(tokens[0], tokens[1], spaces(tokens[2]), spaces(tokens[3]), spaces(tokens[4]), tokens[5]);

    return in;
}

Tutorial CreateTutorial::create_tutorial(const std::string &title, const std::string &presenter, const std::string &minutes, const std::string &seconds, const std::string &likes, const std::string &link)
{
    std::string errors;
    std::string valid_title;
    std::string valid_presenter;
    int min = 0, sec = 0, l = 0;
    std::string valid_link;
    try {
        valid_title = Validator::is_string_empty(title);
    } catch (ValidationException& e) {
        errors += "\nTitle Error: " + std::string (e.which_message());
    }

    try {
        valid_presenter = Validator::is_string_empty(presenter);
    } catch (ValidationException& e) {
        errors += "\nPresenter Error: " + std::string (e.which_message());
    }

    try {
        min = Validator::string_to_int(minutes);
    } catch (ValidationException& e) {
        errors += "\nTMinutes Error: " + std::string (e.which_message());
    }

    try {
        sec = Validator::string_to_int(seconds);
    } catch (ValidationException& e) {
        errors += "\nSeconds Error: " + std::string (e.which_message());
    }

    try {
        l = Validator::string_to_int(likes);
    } catch (ValidationException& e) {
        errors += "\nLikes Error: " + std::string (e.which_message());
    }

    try {
        valid_link = Validator::is_string_empty(link);
    } catch (ValidationException& e) {
        errors += "\nLink Error: " + std::string (e.which_message());
    }

    if (!errors.empty())
        throw ValidationException(errors);
    return Tutorial(valid_title, valid_presenter, Duration(min, sec), l, valid_link);
}