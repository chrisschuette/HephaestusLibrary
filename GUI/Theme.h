/* 
 * File:   Theme.h
 * Author: chris
 *
 * Created on February 10, 2014, 12:15 AM
 */

#ifndef THEME_H
#define	THEME_H

#include "../LOG/Source.h"
#include "TypeID.h"
#include "Context.h"
#include <string>
#include <map>

namespace GUI {
    class ComponentView;
    class Component;
    class Theme : public LOG::Source {
    public:
        typedef ComponentView* (*tCreator)(Component& cmp, Context& ctx);
        typedef std::map<TypeID, tCreator> tCreatorMap;
    public:
        Theme(std::string name);
        ComponentView * getComponentView(TypeID ID, Component& cmp, Context& ctx);
        void registerCreator(const TypeID ID, tCreator creator);
        virtual ~Theme();
    private:
        std::string m_name;
        tCreatorMap m_CreatorMap;

    };
}
#endif	/* THEME_H */

