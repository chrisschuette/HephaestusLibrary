/* 
 * File:   Token.h
 * Author: chris
 *
 * Created on March 8, 2014, 2:00 AM
 */

#ifndef TOKEN_H
#define	TOKEN_H

#include <string>

namespace LEX {

    class Token : public std::string {
    public:

        typedef enum {
            TT_UNKNOWN,
            TT_STRING,
            TT_WORD,
            TT_LITERAL
        } TOKENTYPE;
    public:
        Token();
        virtual ~Token();

        void reset();

        void setTokenType(TOKENTYPE ttype) {
            m_tokenType = ttype;
        }
        TOKENTYPE getTokenType() const {
            return m_tokenType;
        }
    private:
        TOKENTYPE m_tokenType;
    };
}
#endif	/* TOKEN_H */

