#include <gtest/gtest.h>
#include <filesystem>
#include <vector>
#include "../src/lsall.cpp"
//#include "test.cpp"
#include <string>
#include <sstream>
//#include <set>

using std::filesystem::file_type;
using std::filesystem::file_status;
namespace fs=std::filesystem;


struct arguments{
    std::string path = ".";
    bool showemojis = true;
    bool showsize = false;
    bool showpath = false;
    bool onlydirs = false; //## not in order.
    char r_start = '|';
    char r = '~';
    int depth=-1;
    std::vector<std::string> toignore = {};
    //onlydirs in order
};



class demostatus_Test: public testing::Test{};

std::string demostatus_for_testing(fs::file_status filestatus,bool emojis){
    testing::internal::CaptureStdout();
    demo_status(filestatus,emojis,"xx.xx");
    return testing::internal::GetCapturedStdout();
}

TEST_F(demostatus_Test, test_regular){
    fs::file_status file_status(file_type::regular);

    std::string result = demostatus_for_testing(file_status,true);
    EXPECT_TRUE(result.find("📃") != std::string::npos) << "demostatus output for a regular file doesn't contain expected emoji";
    EXPECT_TRUE(result.find(FG_RESET) != std::string::npos) << "demostatus output for a regular file doesn't contain the base reset character.";
}

TEST_F(demostatus_Test, test_directory){
    fs::file_status file_status(file_type::directory);

    std::string result = demostatus_for_testing(file_status,true);
    EXPECT_TRUE(result.find("📁") != std::string::npos) << "demostatus output for a directory doesn't contain expected emoji";
    EXPECT_TRUE(result.find(BASE_DIRECTORY_COLOR) != std::string::npos) << "demostatus output for a directory doesn't contain the base color for directories.";
}


TEST_F(demostatus_Test, test_symlink){
    fs::file_status file_status(file_type::symlink);

    std::string result = demostatus_for_testing(file_status,true);
    EXPECT_TRUE(result.find("🔗") != std::string::npos) << "demostatus output for a symlink doesn't contain expected emoji";
    EXPECT_TRUE(result.find(BASE_SYMLINK_COLOR) != std::string::npos) << "demostatus output for a symlink doesn't contain the base color for a symlink.";
}

TEST_F(demostatus_Test, test_block){
    fs::file_status file_status(file_type::block);

    std::string result = demostatus_for_testing(file_status,true);
    EXPECT_TRUE(result.find("⬛") != std::string::npos) << "demostatus output for a block file doesn't contain expected emoji";
    EXPECT_TRUE(result.find(BASE_BLOCK_COLOR) != std::string::npos) << "demostatus output for block file doesn't contain the base color for a block file.";
}

TEST_F(demostatus_Test, test_character){
    fs::file_status file_status(file_type::character);

    std::string result = demostatus_for_testing(file_status,true);
    EXPECT_TRUE(result.find("c") != std::string::npos) << "demostatus output for a character file doesn't contain expected emoji";
    EXPECT_TRUE(result.find(BASE_CHARACTER_COLOR) != std::string::npos) << "demostatus output for character file doesn't contain the base color for a character file.";
}


