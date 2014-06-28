#include "string.h"
#include <cstdlib>

namespace UTIL {

    std::string getRandomString(int length) {
        static const char alphanum[] =
                "0123456789"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz";

        std::string randomString;
        for (int i = 0; i < length; ++i)
            randomString.push_back(alphanum[rand() % (sizeof (alphanum) - 1)]);
        return randomString;
    }

}