/* 
 * File:   Lexer.cpp
 * Author: chris
 * 
 * Created on March 8, 2014, 1:58 AM
 */

#include "Lexer.h"
#include "Token.h"
#include "../ERR/ERR.h"
#include "../LOG/Core.h"

#define NAME "Lexer"

namespace LEX {

    Lexer::Lexer()
    : m_buffer(0)
    , m_script_p(0)
    , m_end_p(0)
    , m_lastScript_p(0)
    , m_whiteSpaceStart_p(0)
    , m_whiteSpaceEnd_p(0)
    , m_length(0)
    , m_line(0)
    , m_lastline(0)
    , m_loaded(false) {
    }

    Lexer::~Lexer() {
    }

    void Lexer::loadFromMemory(const char* data, int bytes) {
        m_length = bytes;
        m_buffer = data;
        m_script_p = data;
        m_lastScript_p = data;
        m_end_p = &(m_buffer[m_length]);
        m_line = 0;
        m_loaded = true;
    }

    bool Lexer::readString(Token& token, char quoteCharacter) {
        int tmpline;
        const char *tmpscript_p;
        char ch;

        if (quoteCharacter == '\"')
            token.setTokenType(Token::TT_STRING);
        else
            token.setTokenType(Token::TT_LITERAL);


        // leading quote
        m_script_p++;

        while (1) {
            if (*m_script_p == quoteCharacter) {
                // step over the quote
                m_script_p++;
                break;
            } else {
                if (*m_script_p == '\0') {
                    L(error) << "missing trailing quote";
                    return false;
                }
                if (*m_script_p == '\n') {
                    L(error) << "newline inside string";
                    return false;
                }
                token.append(1, *m_script_p++);
            }
        }

        if (token.getTokenType() == Token::TT_LITERAL) {
            if (token.size() != 1) {
                L(warning) << "literal is not one character long";
            }
        }
        return true;
    }

    bool Lexer::readWord(Token& token) {
        char c;

        token.setTokenType(Token::TT_WORD);
        do {
            token.append(1, *m_script_p++);
            c = *m_script_p;
        } while ((c >= 'a' && c <= 'z') ||
                (c >= 'A' && c <= 'Z') ||
                (c >= '0' && c <= '9') ||
                (c == '_') || (c == '-') ||
                (c == '/') || (c == '\\') || (c == ':') || (c == '.'));
        //	token->subtype = token->Length();
        return true;
    }

    Lexer& Lexer::operator>>(Token& token) {
        if (!readToken(token))
            THROWS("Unable to read token.");
        return *this;
    }

    bool Lexer::expectTokenString(const char *string) {
        Token token;

        if (!readToken(token)) {
            L(error) << "couldn't find expected " << string;
            return false;
        }
        if (token != string) {
            L(error) <<  "expected \'" << string << "\' but found \'" <<token  << "\'";
            return false;
        }
        return true;
    }

    bool Lexer::readToken(Token& token) {
        if (!m_loaded) {
            L(error) << "idLexer::ReadToken: no file loaded";
            return false;
        }

        // save script pointer
        m_lastScript_p = m_script_p;
        // save line counter
        m_lastline = m_line;

        // reset token
        token.reset();

        m_whiteSpaceStart_p = m_script_p;
        // read white space before token
        if (!readWhiteSpace()) {
            return false;
        }
        m_whiteSpaceEnd_p = m_script_p;

        char c = *m_script_p;

        if (c == '\"' || c == '\'') {
            if (!readString(token, c)) {
                return false;
            }
        } else if (!readWord(token)) {
            return false;
        }

        return true;

    }

    bool Lexer::readWhiteSpace() {
        while (1) {
            // skip white space
            while (*m_script_p <= ' ') {
                if (!*m_script_p) {
                    return false;
                }
                if (*m_script_p == '\n') {
                    m_line++;
                }
                m_script_p++;
            }
            // skip comments
            if (*m_script_p == '/') {
                // comments //
                if (*(m_script_p + 1) == '/') {
                    m_script_p++;
                    do {
                        m_script_p++;
                        if (!*m_script_p) {
                            return false;
                        }
                    } while (*m_script_p != '\n');
                    m_line++;
                    m_script_p++;
                    if (!*m_script_p) {
                        return false;
                    }
                    continue;
                }// comments /* */
                else if (*(m_script_p + 1) == '*') {
                    m_script_p++;
                    while (1) {
                        m_script_p++;
                        if (!*m_script_p) {
                            return false;
                        }
                        if (*m_script_p == '\n') {
                            m_line++;
                        } else if (*m_script_p == '/') {
                            if (*(m_script_p - 1) == '*') {
                                break;
                            }
                            if (*(m_script_p + 1) == '*') {
                                L(warning) << "nested comment.";
                            }
                        }
                    }
                    m_script_p++;
                    if (!*m_script_p) {
                        return false;
                    }
                    m_script_p++;
                    if (!*m_script_p) {
                        return false;
                    }
                    continue;
                }
            }
            break;
        }
        return true;
    }

}
