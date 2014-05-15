/* 
 * File:   View.h
 * Author: chris
 *
 * Created on February 2, 2014, 5:54 PM
 */

#ifndef VIEW_H
#define	VIEW_H

#include "Element.h"
#include <list>

namespace VIEW {
    struct ViewVisitor {
        virtual void operator()(Element * pComponent)=0;
    };
    
    struct ConstViewVisitor {
        virtual void operator()(const Element * pComponent)=0;
    };
    
    class View : public Element {
    // copies of views are forbidden
    private:    
        View(const View& orig) {}
    public:
        typedef std::list<Element *> tViewList;
        View();
        virtual ~View();

        //rendering
        virtual void renderChildren(Context& pContext) const;

        /*
         *      THE HIERARCHY of Views
         */

        // children
        virtual void addChild(Element * pChild);
        virtual void removeChild(Element * pChild);
        virtual void removeAllChildren();
        bool hasChildren();
        int getChildCount();
        //Component* getChild(int i) const;
        const tViewList& getChildren() const { return m_children; }
        tViewList& getChildren() { return m_children; }
        
        virtual void addToList(std::list<Element*>& elements);
        virtual std::list<Element*> getListOfElements();
        
        //validity
        virtual void validate();
        
    protected:
        tViewList m_children;
    };
}
#endif	/* VIEW_H */

