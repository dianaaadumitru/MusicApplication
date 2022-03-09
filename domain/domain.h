#pragma once
#include <iostream>
#include "../validator/validator.h"
#include "../utils/utils.h"

class Duration
{
private:
    int minutes, seconds;

public:
    Duration() : minutes(0), seconds(0) {};

    //constructor
    Duration(int min, int sec): minutes(min), seconds(sec) {};

    //getters and setters

    int getMinutes() const { return minutes; }
    int getSeconds() const { return seconds; }
    void setMinutes(int min) { minutes = min; }
    void setSeconds(int sec) { seconds = sec; }

};

class Tutorial
{
private:
    /*
     * UNIQUELY IDENTIFIED BY THEIR PRESENTER AND TITLE
     */
    std::string title;
    std::string presenter;
    Duration duration;
    int likes;
    std::string link;
public:
    // default constructor for a playlist
    Tutorial();
//    ~Tutorial();

    // constructor with parameters
    Tutorial(const std::string& title, const std::string& presenter, const Duration& duration, const int& likes, const std::string& link);
    static Tutorial create_tutorial(const std::string & title,const std::string & presenter, const std::string & minutes, const std::string & seconds, const std::string & likes, const std::string & link);
    //getters and setters
    std::string get_title() const;
    std::string get_presenter() const;
    int get_no_of_likes() const;
    std::string get_link() const;
    Duration get_duration() const;
    void set_presenter(std::string value) { presenter = value; };

    void open_link() const;
    void like();

    // operators overloading
    bool operator==(const Tutorial& t);
    friend std::ostream & operator << (std::ostream &out, const Tutorial &t);
    friend std::istream & operator >> (std::istream &in, Tutorial &t);


};

class CreateTutorial
{
public:
    static Tutorial create_tutorial(const std::string & title,const std::string & presenter, const std::string & minutes, const std::string & seconds, const std::string & likes, const std::string & link);
};