/* 
 * File:   LangDict.cpp
 * Author: chris
 * 
 * Created on March 8, 2014, 8:31 AM
 */

#include "LangDict.h"
#include "../UTIL/hash.h"
#include <iostream>
#include "../LOG/Core.h"

#define NAME "LangDict"

namespace LEX {

    LangDict::LangDict() {
    }

    LangDict::~LangDict() {
    }

    bool LangDict::set(const std::string& key, const std::string& text) {
        // check if already present
        int hash = getHash(key);

        int index = m_index.first(hash);
        while ((index >= 0) && (key != m_entries.at(index).key))
            index = m_index.next(index);
        if (index >= 0) { // already present
            m_entries.at(index).text = text;
        } else { // add new
            m_index.add(hash, m_entries.size());
            m_entries.push_back(LangDictEntry(key, text));
        }
        return true;
    }

    int LangDict::getHash(const std::string& key) {
        return UTIL::hash(key);
    }

    std::string LangDict::getText(const std::string& key) {
        int hash = getHash(key);

        int index = m_index.first(hash);
        while ((index != -1) && (key != m_entries.at(index).key))
            index = m_index.next(index);
        if (index != -1)
            return m_entries.at(index).text;
        else 
            return std::string();
    }


}
