#include <string>
#include <sstream>
#include <iostream>
#include <streambuf>
#include <functional>
#include <ios>

class callback_streambuf : public std::streambuf {
public:
    callback_streambuf(std::function<void(char const*, std::streamsize)> callback) : callback(callback) {}

protected:
    std::streamsize xsputn(char_type const* s, std::streamsize count) {
        callback(s, count);
        return count;
    }

private:
    std::function<void(char const*, std::streamsize)> callback;
};

std::streambuf* oldcoutbuf = std::cout.rdbuf();


void redirect_cout(std::ostringstream& strcout){
    std::cout.rdbuf(strcout.rdbuf());
}

void reverse_redirect_cout(){
    std::cout.rdbuf(oldcoutbuf);
}


