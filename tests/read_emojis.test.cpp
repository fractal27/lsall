#include <gtest/gtest.h>
#include <filesystem>
#include <vector>
#include "../src/read_emojis.cpp"
#include "test.cpp"
#include <string>
#include <sstream>
//#include <set>

namespace fs=std::filesystem;


//std::string result;
class read_emojis_Test: public testing::Test{};

TEST_F(read_emojis_Test, image){
    std::string result = emoji::get_emoji("png");
    ASSERT_EQ(result,"📷") << "png emoji incorrect";
    result = emoji::get_emoji("jpg");
    ASSERT_EQ(result,"📷") << "jpg emoji incorrect";
    result = emoji::get_emoji("jpeg");
    ASSERT_EQ(result,"📷") << "jpeg emoji incorrect";
    result = emoji::get_emoji("webp");
    ASSERT_EQ(result,"📷") << "webp emoji incorrect";
}

TEST_F(read_emojis_Test, icon){
    std::string result = emoji::get_emoji("ico");
    ASSERT_EQ(result,"👤") << "ico emoji incorrect";
}
TEST_F(read_emojis_Test, markdown){
    std::string result = emoji::get_emoji("md");
    ASSERT_EQ(result,"📜") << "md emoji incorrect";
}
TEST_F(read_emojis_Test, camel){
    std::string result = emoji::get_emoji("ml");
    ASSERT_EQ(result,"🐫") << "ml emoji incorrect";
    result = emoji::get_emoji("mli");
    ASSERT_EQ(result,"🐫") << "mli emoji incorrect";
}
