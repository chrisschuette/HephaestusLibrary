/* 
 * File:   Component.h
 * Author: chris
 *
 * Created on February 2, 2014, 5:56 PM
 */

#ifndef ELEMENT_H
#define	ELEMENT_H

#include <list>

namespace VIEW {
    class Context;
    class View;
    class Element {
    public:
        Element();
        Element(const Element& orig);
        virtual ~Element();

        //rendering
        virtual void render(Context& pContext) const = 0;

        //validity
        virtual void validate() { m_valid = true; }
        virtual void invalidate();
        bool isValid() const { return m_valid; }
        
        //visibility
        void setVisible(bool visible) { m_visible = visible; }
        bool isVisible() const { return m_visible; }
        
        //selectable
        void setSelectable(bool selectable) { m_selectable = selectable; }
        bool isSelectable() const { return m_selectable; }

        // parent
        void setParent(View* parent) { m_pParent = parent; }
        View* getParent() const { return m_pParent; }
        
        // find all elements
        virtual void addToList(std::list<Element*>& elements) { elements.push_back(this); }
        
    protected:
        View * m_pParent;
        bool m_valid;
        bool m_visible;
        bool m_selectable;
    };
}
#endif	/* ELEMENT_H */

