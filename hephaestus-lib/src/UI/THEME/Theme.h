/* 
 * File:   Theme.h
 * Author: chris
 *
 * Created on May 23, 2014, 8:01 PM
 */

#ifndef THEME_H
#define	THEME_H

#include <map>

namespace UI {
    class Component;
    class Context;
    class ComponentView;
    namespace THEME {
        class Theme {
        public:
            Theme();
            virtual ~Theme();
            ComponentView* createComponentView(Component& cmp, Context& ctx) const;
        protected:
            typedef ComponentView* (*tCreator)(Component& cmp, Context& ctx);
            typedef std::map<unsigned int, tCreator> tCreatorMap;
            void registerCreator(unsigned int typeID, tCreator creator);
        private:
            tCreatorMap m_creatorMap;
        };
    }
}
#endif	/* THEME_H */

