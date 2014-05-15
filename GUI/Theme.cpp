/* 
 * File:   Theme.cpp
 * Author: chris
 * 
 * Created on February 10, 2014, 12:15 AM
 */

#include "Theme.h"

namespace GUI {

    Theme::Theme(std::string name) : LOG::Source("THEME::" + name), m_name(name) {
    }

    ComponentView * Theme::getComponentView(TypeID ID, Component& cmp, Context& ctx) {
        tCreatorMap::iterator i = m_CreatorMap.find(ID);
        if (i != m_CreatorMap.end()) {
            tCreator aCreator = (*i).second;
            L(normal) << "Created ComponentView ID=" << ID.getID();
            return aCreator(cmp, ctx);
        }
        return 0;
    }
    
    void Theme::registerCreator(const TypeID ID, tCreator creator) {
        m_CreatorMap.insert(std::pair<TypeID, tCreator>(ID,creator));
    }

    Theme::~Theme() {
    }
}
