#include <json/value.h> //json reading
#include <json/json.h> //json reading

#include <string>
#include <fstream>
#include "lsall.h"      //(#include <filesystem>)
#include "read_emojis.h"//all class definitions
#include <iostream>
#include <sstream>      //file handling
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>


namespace fs = std::filesystem;


namespace emoji{

    fs::path get_path(){
        // get emoji cofniguration path ()
		const char *homedir;

		if ((homedir = getenv("HOME")) == NULL) {
			homedir = getpwuid(getuid())->pw_dir;
		}

		std::string config_home_path = homedir;
		config_home_path += "/.config/lsall/ext_emoji.json";

        if(fs::exists("/etc/lsall/ext_emoji.json")){
             return fs::path("/etc/lsall/ext_emoji.json");
        } else if(fs::exists(config_home_path)){
             return fs::path(config_home_path);
        } else {
             return fs::path("ext_emoji.json");
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
