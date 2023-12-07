#include <string>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>


#include <lsall.h>

#include <stdio.h>

//#include "execute.cpp"
//#define areemojisupported execute_command("areemojisupported.sh")==0


void show_help(){
    std::cout   <<"Usage: lsall [-ifFesp] [<path1> <path2> ... <pathn>]" << std::endl
                <<"\t-h -?   \tShow help." << std::endl
                <<"\t-i      \tGet from input(with no prompt.)." << std::endl
                <<"\t-f CHAR \tChange the start character of every line." << std::endl
                <<"\t-F CHAR \tFiller da mettere tra l'inizio della linea e il nome file." << std::endl
                <<"\t-e      \tDisabilita le emoji." << std::endl
                <<"\t-s      \tShow the size of every file.." << std::endl
                <<"\t-p PATH \tShow only one tree(the tree of the path argument)" << std::endl
                <<"\t-d DEPTH\tSets the depth of the recursive search." << std::endl
                <<"\t-D      \tShows only the directories in the file tree." << std::endl
                //<<"\t--only-dirs     \tSets the depth of the recursive search." << std::endl
                <<"\t-x      \tExcludes via linux pattern(* and ? must be escaped)"
                              "all the paths that match the pattern." << std::endl;
}

int main(int argc,char** argv){
    // Normal modes and parsing
    bool INPUTMODE = false;
    bool SHOWSIZE = false;
    bool DISABLEEMOJI = false;
    bool SHOW_PATH = false;
    bool ONLY_DIRS = false;

    // Arguments with necessary parameters
    char r_start = '|';
    char r_char = '~';
    std::vector<std::string> exclude_patterns {};
    std::string path = ".";
    int depth = -1;

    char c;
    bool done = false;
    
    // Use getopt to search through arguments and set modes
    while ((c=getopt(argc, argv, "p:F:f:esid:x:D"))!=-1) {
        switch(c){
            case 'd':
                depth = std::atoi(optarg);
                continue;
            case 'D':
                ONLY_DIRS = true;
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
            case 'x':
                exclude_patterns.push_back(std::string(optarg));
                continue;
            default:

                fprintf(stderr,"Argument -%c not found: here is commands:\n",c);
                show_help();
                std::exit(1);
            case -1:
                break;
        }
    }
    std::cout << "ONLY_DIRS:" << ONLY_DIRS<<std::endl;
    //for debugging argument -x
    //std::cout << "excludes:" << std::endl;
    //for(std::string s:exclude_patterns){
    //    std::cout << "\t" << s << std::endl;
    //}
    if(INPUTMODE){

        std::cin >> path;
        std::cout << BASE_DIRECTORY_COLOR << "[" << path << "]" << FG_RESET<< std::endl;
        
        lsall(path,!DISABLEEMOJI,SHOWSIZE, SHOW_PATH,
              r_start,r_char,depth, exclude_patterns, ONLY_DIRS);
        
        done = true;
    } else {
        for (; optind < argc; optind++){
            path = argv[optind];
            std::cout << BASE_DIRECTORY_COLOR << "[" << path << "]" << FG_RESET<< std::endl;
            lsall(path,!DISABLEEMOJI, SHOWSIZE, SHOW_PATH,
                  r_start, r_char, depth, exclude_patterns, ONLY_DIRS);
            done=true;
        }
    }
    if(!done){
        std::cout << BASE_DIRECTORY_COLOR << "[" << path << "]" << FG_RESET<< std::endl;
        lsall(path,!DISABLEEMOJI, SHOWSIZE, SHOW_PATH,
              r_start, r_char, depth, exclude_patterns, ONLY_DIRS);
    }
    return 0;
}
