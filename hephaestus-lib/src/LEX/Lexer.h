/* 
 * File:   Lexer.h
 * Author: chris
 *
 * Created on March 8, 2014, 1:58 AM
 */

#ifndef LEXER_H
#define	LEXER_H

namespace LEX {
    class Token;
    class Lexer {
    public:
        Lexer();
        virtual ~Lexer();

        void loadFromMemory(const char* data, int bytes);
        bool readToken(Token& token);
        bool expectTokenString( const char *string );

        Lexer& operator>>(Token& token);
    private:
        bool readWhiteSpace();
        bool readString( Token& token, char quoteCharacter );
        bool readWord( Token& token );
        const char * m_buffer; // buffer containing the script
        const char * m_script_p; // current pointer in the script
        const char * m_end_p; // pointer to the end of the script
        const char * m_lastScript_p;
        const char * m_whiteSpaceStart_p;
        const char * m_whiteSpaceEnd_p;
        int m_length;
        int m_line; // current line in script
        int m_lastline;
        bool m_loaded;
    };
}
#endif	/* LEXER_H */

