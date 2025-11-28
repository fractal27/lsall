#ifndef _READ_EMOJIS_H
#define _READ_EMOJIS_H

#include <exception>
#include <string>
#include <filesystem>
namespace fs = std::filesystem;


namespace emoji{
    /*Emoji configuration related*/
    fs::path get_path();
    std::string get_emoji(std::string);
}


class FileNotFound: public std::exception{
    virtual const char* what() const throw(){
        return "File was not found during emoji json file search.";
    }
};

#endif


