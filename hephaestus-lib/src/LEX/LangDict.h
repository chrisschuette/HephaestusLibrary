/* 
 * File:   LangDict.h
 * Author: chris
 *
 * Created on March 8, 2014, 8:31 AM
 */

#ifndef LANGDICT_H
#define	LANGDICT_H

#include <string>
#include <vector>
#include "../MEM/HashIndex.h"

namespace LEX {

    struct LangDictEntry {
        std::string key;
        std::string text;

        LangDictEntry(const std::string& k, const std::string& t)
        : key(k)
        , text(t) {
        }
    };

    class LangDict {
    public:
        LangDict();
        virtual ~LangDict();

        bool set(const std::string& key, const std::string& text);
        std::string getText(const std::string& key);
    private:
        int getHash(const std::string& key);
        MEM::HashIndex m_index;
        std::vector<LangDictEntry> m_entries;
    };
}
#endif	/* LANGDICT_H */

