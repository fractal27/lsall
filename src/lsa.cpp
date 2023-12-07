#include <vector>
#include <filesystem>
#include <sstream>
#include <algorithm>
#include <string>
#include <iostream>
#include <unistd.h>
#include <ranges>
#include <stdlib.h>
#include <cmath>
#include <lsall.h>
#include <stdio.h>
#include <fstream>
#include <fnmatch.h>


namespace fs = std::filesystem;



static void demo_status(fs::file_status s,bool emoji){
    if(emoji){                              
        switch (s.type()){                      
            case fs::file_type::regular:
                std::cout << "📃 " << FG_RESET;
                break;
            case fs::file_type::directory:
                std::cout << "📁 " << BASE_DIRECTORY_COLOR;
                break;
            case fs::file_type::symlink:
                std::cout << "🔗 " << BASE_SYMLINK_COLOR;
                break;
            case fs::file_type::block:
                std::cout << "⬛ " << BASE_BLOCK_COLOR;
                break; 
            case fs::file_type::character:
                std::cout << "c " << BASE_CHARACTER_COLOR;
                break;
            default:
                std::cout << "? " << BASE_OTHER_COLOR;
                break;
        }
    } else {
                                            
        switch (s.type()){                      
            case fs::file_type::regular:
                std::cout << FG_RESET << "(r) ";
                break;
            case fs::file_type::directory:
                std::cout << BASE_DIRECTORY_COLOR << "(d) ";
                break;
            case fs::file_type::symlink:
                std::cout << BASE_SYMLINK_COLOR << "(s) ";
                break;
            case fs::file_type::block:
                std::cout << BASE_BLOCK_COLOR << "(b) ";
                break;
            case fs::file_type::character:
                std::cout << BASE_CHARACTER_COLOR << "(c) ";
                break;
            default:
                std::cout << BASE_OTHER_COLOR << "(?) ";
                break;
        }                                       //switch end
    }                                       //else end
};

struct HumanReadable
{
    std::uintmax_t size{};

private:
    friend std::ostream& operator<<(std::ostream& os, HumanReadable hr)
    {
        int o{};
        double mantissa = hr.size;
        for (; mantissa >= 1024.; mantissa /= 1024., ++o);

        os << "[" << std::ceil(mantissa * 10.) / 10. << "BKMGTPE"[o];
        return (o ? os << "B": os) << "] ";
   }
};

static bool doesskip(std::string str,std::vector<std::string> exclude_str){
    for(std::string cstr:exclude_str){
        std::string parsed;
        std::stringstream input_sstream(str);
        while(getline(input_sstream,parsed,'/'))
            if(fnmatch(cstr.c_str(),parsed.c_str(),{})==0){
                return true;
            };
    }
    return false;
}
/*
static std::vector<std::string> getlines_asvector(std::string filename){
    std::fstream newfile;
    std::vector<std::string> lines;
    newfile.open(filename,std::ios::in); //open a file to perform read operation using file object
    if (newfile.is_open()){              //checking whether the file is open
        std::string tp;
        while(getline(newfile, tp)){     //read data from file object and put it into string.
            lines.push_back(tp);
        }
        newfile.close();                 //close the file object.
    }
    return lines;
}*/

static void lsall(std::string path,bool showemojis=true,bool showsize=false,
                  bool showpath = false, char r_start='|', char r = '~', int depth=-1,
                  std::vector<std::string> toignore = {}, bool onlydirs=false){
/*
static void lsall(std::string path,bool showemojis,bool showsize,
                  bool showpath, char r_start, char r ,int depth,
                  std::vector<std::string> toignore ,bool onlydirs){
*/
    std::string str;
    std::string cstr;
    std::string last_element;
    
    auto get_last =
            showpath?[](std::string str){return str;}
                    :[](std::string str){return std::string(str.substr(str.rfind('/') + 1));};

    if(toignore.size()){
        if(depth>=0){
            for (auto i = fs::recursive_directory_iterator(path);
                i != fs::recursive_directory_iterator();
                i++){
                if(i.depth() > depth) continue;
                if(onlydirs && !fs::is_directory(*i)) continue;
                //std::cout << fs::is_directory(*i)?"<dir> ":"<file> ";

                str = (*i).path();
                if (doesskip(str,toignore)) continue;


                std::cout << r_start;
                std::cout << std::string(1 + (i.depth() << 1), r);
                
                demo_status(i->symlink_status(),showemojis);
                if(showsize && !fs::is_directory(*i)){
                    try{
                        std::cout << HumanReadable{fs::file_size(*i)};
                    } catch (fs::filesystem_error const&){};
                }
            
                last_element = get_last(str);

                std::cout << last_element << "\033[0m" << std::endl;
            };
        } else {
            for (auto i = fs::recursive_directory_iterator(path);
                i != fs::recursive_directory_iterator();
                i++){

                if(onlydirs && !fs::is_directory(*i)) continue;
                //std::cout << fs::is_directory(*i)?"<dir> ":"<file> ";

                str = (*i).path();
                if(doesskip(str,toignore)) continue;
                std::cout << r_start;
                std::cout << std::string(1 + (i.depth() << 1), r);


                demo_status(i->symlink_status(),showemojis);
                if(showsize && !fs::is_directory(*i)){
                    try{
                        std::cout << HumanReadable{fs::file_size(*i)};
                    } catch (fs::filesystem_error const&){};
                }
                
                last_element = get_last(str);
                std::cout << last_element << "\033[0m" << std::endl;
            };
        }
    } else {
        if(depth>=0){
            for (auto i = fs::recursive_directory_iterator(path);
                    i != fs::recursive_directory_iterator();
                    i++){
                if(onlydirs && !fs::is_directory(*i)) continue;
                if(i.depth() > depth) continue;
                std::cout << r_start;
                std::cout << std::string(1 + (i.depth() << 1), r);
                str = (*i).path();
        
                demo_status(i->symlink_status(),showemojis);
                if(showsize && !fs::is_directory(*i)){
                    try{
                        std::cout << HumanReadable{fs::file_size(*i)};
                    } catch (fs::filesystem_error const&){};
                }
            
                ////last_element = std::string(str.substr(str.rfind('/') + 1));
                last_element = get_last(str);
                std::cout << last_element << "\033[0m" << std::endl;
            };
        } else {
            for (auto i = fs::recursive_directory_iterator(path);
                i != fs::recursive_directory_iterator();
                i++){
                if(onlydirs && !fs::is_directory(*i)) continue;

                std::cout << r_start;
                std::cout << std::string(1 + (i.depth() << 1), r);
                str = (*i).path();
        
                demo_status(i->symlink_status(),showemojis);
                if(showsize && !fs::is_directory(*i)){
                    try{
                        std::cout << HumanReadable{fs::file_size(*i)};
                    } catch (fs::filesystem_error const&){};
                }
                
                //last_element = std::string(str.substr(str.rfind('/') + 1));
                last_element = get_last(str);
                std::cout << last_element << "\033[0m" << std::endl;
            };
        }
    }
};


