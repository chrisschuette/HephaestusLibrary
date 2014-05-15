/* 
 * File:   View.cpp
 * Author: chris
 * 
 * Created on February 2, 2014, 5:54 PM
 */

#include "View.h"
#include <algorithm>

namespace VIEW {

    struct ViewValidator : public ViewVisitor {
        virtual void operator()(Element * pComponent) {
            pComponent->validate();
        }
    };
    
    struct ViewLister : public ViewVisitor {
        ViewLister(std::list<Element*>& list) : m_list(list) {} 
        
        virtual void operator()(Element * pComponent) {
            m_list.push_back(pComponent);
        }
    private:
        std::list<Element*>& m_list;
    };
    
    struct ViewRenderer : public ConstViewVisitor {
        ViewRenderer(Context& context) : m_pContext(context) {} 
        
        virtual void operator()(const Element * pComponent) {
            pComponent->render(m_pContext);
        }
    private:
        Context& m_pContext;
    };

    struct ViewDeleter {
        inline void operator()(Element * pComponent) {
            delete pComponent;
        }
    };
    
View::View()
: Element() {
    m_selectable = false;
}

void View::renderChildren(Context& pContext) const {
    std::for_each(m_children.begin(), m_children.end(), ViewRenderer(pContext));
}

void View::addChild(Element * const pChild) {
    m_children.push_back(pChild);
    pChild->setParent(this);
}

void View::removeChild(Element * const pChild) {
    tViewList::iterator i = std::find(m_children.begin(), m_children.end(), pChild);
    if (i != m_children.end()) {
        m_children.erase(i);
        delete pChild;
    }
}

void View::removeAllChildren() {
    std::for_each(m_children.begin(), m_children.end(), ViewDeleter());
}

bool View::hasChildren() {
    return (m_children.size() != 0);
}
/*
Component* View::getChild(int i) const {
    return m_children.at(i);
}
*/
void View::addToList(std::list<Element*>& elements) {
    elements.push_back(this);
    
    ViewLister lister(elements);
    std::for_each(m_children.begin(), m_children.end(), lister);
}

std::list<Element*> View::getListOfElements() {
    std::list<Element*> list;
    addToList(list);
    return list;
}

int View::getChildCount() {
    return m_children.size();
}

View::~View() {
    std::for_each(m_children.begin(), m_children.end(), ViewDeleter());
}

void View::validate() {
    if (!isValid()) {
        std::for_each(m_children.begin(), m_children.end(), ViewValidator());
        Element::validate();
    }
}

}

