/* 
 * File:   LangDict.cpp
 * Author: chris
 * 
 * Created on March 8, 2014, 12:13 PM
 */

#include "LangDict.h"
#include "../LEX/Lexer.h"
#include "../LEX/Token.h"

namespace LOC {

    LangDictLoader::LangDictLoader() : FSVR::Loader("LangDictLoader") {

    }

    LangDictLoader::~LangDictLoader() {

    }

    void LangDictLoader::instantiate(FSVR::Resource& resource, const FSVR::ResourceMetaData& metadata) {
        LEX::Lexer lex;
        lex.loadFromMemory((const char*) getRawData(), getRawDataSize());

        LangDict& langDict = static_cast<LangDict&>(resource);
        // create a lexer feed it with the text file contents buffer
        // extract token tuples and add them to the LangDict
        
        LEX::Token key, value;
        
        lex.expectTokenString("{");
        int tupleCounter = 0;
        while( lex.readToken( key ) ) {
            if( key == "}" ) {
                break;
            }
            if( lex.readToken(value) ) {
                // add to dictionary
                langDict.set(key, value);
                tupleCounter++;
            }
        }
        L(normal) << "Loaded " << tupleCounter << " tuples.";

        
        FSVR::Loader::instantiate(resource, metadata);
    }

    LangDict::LangDict(const FSVR::tRID& rid)
    : FSVR::Resource(rid)
    , LEX::LangDict()
    {
        setInstantiation(FSVR::Resource::IMMEDIATELY);
    }

    LangDict::~LangDict() {
    }

    FSVR::Loader* LangDict::createLoader() {
        return new LangDictLoader;
    }

}
