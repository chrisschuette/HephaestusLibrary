#include "Hash.h"

namespace INPUT {
    tID hash(const char * identifier) {
        unsigned hashVal;
     
    for( hashVal = 0 ; *identifier != '\0' ; identifier++ )
        hashVal = *identifier + 31 * hashVal;
        
    return hashVal;
    }
}