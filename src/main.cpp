#include <string>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <lsall.h>
#include "lsa.cpp"
#include <stdio.h>

//#include "execute.cpp"
//#define areemojisupported execute_command("areemojisupported.sh")==0


void show_help(){
    std::cout   <<"Usage: lsall [-ifFesp] [<path1> <path2> ... <pathn>]" << std::endl
                <<"\t-h -?\tShow help." << std::endl
                <<"\t-i   \tGet from input(with no prompt.)." << std::endl
                <<"\t-f   \tChange the start character of every line." << std::endl
                <<"\t-F   \tFiller da mettere tra l'inizio della linea e il nome file." << std::endl
                <<"\t-e   \tDisabilita le emoji." << std::endl
                <<"\t-s   \tShow the size of every file.." << std::endl
                <<"\t-p   \tPercorso da vedere la struttura." << std::endl;
}

int main(int argc,char** argv){
    // Normal modes and parsing
    bool INPUTMODE = false;
    bool SHOWSIZE = false;
    bool DISABLEEMOJI = false;
    bool SHOW_PATH = false;
    
    // Arguments with necessary parameters
    char r_start = '|';
    char r_char = '~';
    std::string path = ".";
    int depth = -1;

    int index;
    char c;
    bool done = false;
    
    // Use getopt to search through arguments and set modes
    while ((c=getopt(argc, argv, "p:F:f:esid:"))!=-1) {
        switch(c){
            case 'd':
                depth = std::atoi(optarg);
                continue;
            case 'i':
                INPUTMODE = true;
                continue;
            case 'F':
                r_char = std::string(optarg)[0];
                continue;
            case 'f':
                r_start = std::string(optarg)[0];
                continue;
            case 'p':
                path = std::string(optarg);
                continue;
            case 's':
                SHOWSIZE=true;
                continue;
            case 'S':
                SHOW_PATH=true;
                continue;
            case 'e':
                DISABLEEMOJI = true;
                continue;
            default:
                fprintf(stderr,"Argument -%c not found: here is commands:\n",c);
                show_help();
                std::exit(1);
            case -1:
                break;
        }
    }
    
    if(INPUTMODE){

        std::cin >> path;
        std::cout << BASE_DIRECTORY_COLOR << "[" << path << "]" << FG_RESET<< std::endl;
        
        lsall(path,!DISABLEEMOJI,SHOWSIZE, SHOW_PATH,r_start,r_char,depth);
        
        done = true;
    } else {
        for (; optind < argc; optind++){
            path = argv[optind];
            std::cout << BASE_DIRECTORY_COLOR << "[" << path << "]" << FG_RESET<< std::endl;
            lsall(path,!DISABLEEMOJI,SHOWSIZE, SHOW_PATH,r_start,r_char,depth);
            done=true;
        }
    }
    if(!done){
        std::cout << BASE_DIRECTORY_COLOR << "[" << path << "]" << FG_RESET<< std::endl;
        lsall(path,!DISABLEEMOJI,SHOWSIZE, SHOW_PATH,r_start,r_char,depth);
    }
    return 0;
}
