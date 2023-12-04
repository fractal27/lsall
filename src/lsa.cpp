#include <filesystem>
#include <string>
#include <iostream>
#include <unistd.h>
#include <ranges>
#include <stdlib.h>
#include <cmath>
#include <lsall.h>
#include <stdio.h>


namespace fs = std::filesystem;

static void demo_status(fs::file_status s,bool emoji)
{
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

static void lsall(std::string path,bool showemojis=true,bool showsize=false,
                  bool showpath = false, char r_start='|', char r = '~', int depth=-1){

    std::string str;
    std::string last_element;
    auto get_last =
            showpath?[](std::string str){return str;}
                    :[](std::string str){return std::string(str.substr(str.rfind('/') + 1));};
    if(depth>0){
        for (auto i = fs::recursive_directory_iterator(path);
            i != fs::recursive_directory_iterator();
            i++)
        {
            if(i.depth() > depth) continue;
            std::cout << r_start;
            std::cout << std::string(1 + (i.depth() << 1), r);
            str = (*i).path();
    
            demo_status(i->symlink_status(),showemojis);
            if(showsize && !fs::is_directory(*i)){
                try{
                    std::cout << HumanReadable{fs::file_size(*i)};
                } catch (fs::filesystem_error err) {}
            }
        
            ////last_element = std::string(str.substr(str.rfind('/') + 1));
            last_element = get_last(str);
            std::cout << last_element << "\033[0m" << std::endl;
        };
    } else {
        for (auto i = fs::recursive_directory_iterator(path);
            i != fs::recursive_directory_iterator();
            ++i)
        {
            std::cout << r_start;
            std::cout << std::string(1 + (i.depth() << 1), r);
            str = (*i).path();
    
            demo_status(i->symlink_status(),showemojis);
            if(showsize && !fs::is_directory(*i)){
                try{
                    std::cout << HumanReadable{fs::file_size(*i)};
                } catch (fs::filesystem_error err) {}
            }
            
            //last_element = std::string(str.substr(str.rfind('/') + 1));
            last_element = get_last(str);
            std::cout << last_element << "\033[0m" << std::endl;
        };
    }
};


