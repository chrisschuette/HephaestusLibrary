#include "IO.h"
#include "../ERR/ERR.h"

#include <fstream>

namespace UTIL {

    std::string readTextFile(std::string filename) {
        std::ifstream in(filename.c_str(), std::ios::in | std::ios::binary);
        if (in) {
            std::string contents;
            in.seekg(0, std::ios::end);
            contents.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&contents[0], contents.size());
            in.close();
            return (contents);
        }
        THROWS("Unable to read " + filename);
    }
}