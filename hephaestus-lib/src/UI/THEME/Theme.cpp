/* 
 * File:   Theme.cpp
 * Author: chris
 * 
 * Created on May 23, 2014, 8:01 PM
 */

#include "Theme.h"
#include "../Component.h"

#include <iostream>

namespace UI {
    namespace THEME {

        Theme::Theme() {
        }

        Theme::~Theme() {
        }

        ComponentView* Theme::createComponentView(Component& cmp, Context& ctx) const {
            tCreatorMap::const_iterator i = m_creatorMap.find(cmp.getTypeID());
            if (i != m_creatorMap.end()) {
                tCreator aCreator = (*i).second;
                return aCreator(cmp, ctx);
            }
            return 0;
        }

        void Theme::registerCreator(unsigned int typeID, tCreator creator) {
            m_creatorMap.insert(std::pair<unsigned int, tCreator>(typeID, creator));
        }

    }
}
