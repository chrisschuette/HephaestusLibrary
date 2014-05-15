/* 
 * File:   Token.cpp
 * Author: chris
 * 
 * Created on March 8, 2014, 2:00 AM
 */

#include "Token.h"

namespace LEX {
    Token::Token()
    : std::string()
    , m_tokenType(TT_UNKNOWN)
    {
    }

    Token::~Token() {
    }

    void Token::reset() {
        clear();
    }

}
