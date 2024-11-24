#include <gtest/gtest.h>
#include <filesystem>
#include <vector>
#include "../src/read_emojis.cpp"
#include "test.cpp"
#include <string>
#include <sstream>
//#include <set>

namespace fs=std::filesystem;



class read_emojis_Test: public testing::Test{};

/*TODO: maybe used as test for read_emojis? 
 * std::string demostatus_for_testing(fs::path path,){
    std::ostringstream ss;
    redirect_cout(ss);
    demo_status(filestatus,emojis);
    reverse_redirect_cout();
    return ss.str();
}*/

TEST_F(read_emojis_Test, test_regular){
    fs::path p = "";

    std::string result = demostatus_for_testing(file_status,true);
}

TEST_F(read_emojis_Test, test_directory){
    fs::file_status file_status(file_type::directory);

    std::string result = demostatus_for_testing(file_status,true);
}



