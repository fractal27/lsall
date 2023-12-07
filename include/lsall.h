#include <filesystem>
#include <vector>
#include <string>
#include <iostream>

#define FG_BLACK   "\033[30m"
#define FG_RED     "\033[31m"
#define FG_GREEN   "\033[32m"
#define FG_YELLOW  "\033[33m"
#define FG_BLUE    "\033[34m"
#define FG_MAGENTA "\033[35m"
#define FG_CYAN    "\033[36m"
#define FG_WHITE   "\033[37m"
#define FG_DEFAULT "\033[39m"
#define FG_RESET   "\033[0m"

#define BASE_DIRECTORY_COLOR    FG_CYAN
#define BASE_SYMLINK_COLOR      FG_RED
#define BASE_BLOCK_COLOR        FG_GREEN
#define BASE_CHARACTER_COLOR    FG_MAGENTA
#define BASE_OTHER_COLOR        FG_YELLOW

namespace fs=std::filesystem;


void lsall(std::string path,bool showemojis=true,bool showsize=false,
            bool showpath = false, char r_start='|', char r = '~', int depth=-1,
            std::vector<std::string> toignore = {}, bool onlydirs=false);

static void demo_status(fs::file_status s,bool emoji);

static bool doesskip(std::string str,std::vector<std::string> exclude_str);


