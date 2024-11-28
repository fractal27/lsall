#include <json/value.h> //json reading
#include <json/json.h> //json reading

#include <string>
#include <fstream>
#include "lsall.h"      //(#include <filesystem>)
#include "read_emojis.h"//all class definitions
#include <iostream>
#include <sstream>      //file handling
namespace fs = std::filesystem;


namespace emoji{

    inline fs::path get_path(){
        // get emoji cofniguration path ()
        if(fs::exists("/etc/lsall/ext_emoji.json")){
             return fs::path("/etc/lsall/ext_emoji.json");
        } else if(fs::exists("~/.config/lsall/ext_emoji.json")){
             return fs::path("~/.config/lsall/ext_emoji.json");
        } else {
             return fs::path("emoji_ext.json");
        }
    }

    std::string get_emoji(std::string ext){
        /* Takes the emoji from a json file. */
        static fs::path emoji_config_path;
        if(emoji_config_path.empty()){
            emoji_config_path = emoji::get_path();
        }

        std::ifstream emoji_file(emoji_config_path, std::ifstream::binary);
        std::stringstream s;
        Json::Value emojis;

        if(emoji_file){
            s << emoji_file.rdbuf();
            s >> emojis;

            return std::string(emojis[ext].asString());
        } else {
            throw FileNotFound();
        }
    };
};
